/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Ivailov Georgiev
* @idnumber 45115
* @task 1
* @compiler VC
*
*/
#include <iostream>
#include <fstream>
#include "Trie.h"

#include <cstdio>
#include <ctime>

using namespace std;

static bool isLetter(char c)
{
	return c >= 'a' && c <= 'z';
}

static char tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;

	return c;
}

static unsigned long long getContentLength(ifstream& is)
{
	streampos start = is.tellg();
	is.seekg(0, std::ios::end);
	unsigned long long inputLenght = (is.tellg() - start) / sizeof(char);
	is.seekg(0, std::ios::beg);
	is.clear();
	return inputLenght;
}

static char* readChars(int count, ifstream& is)
{
	char* readed = new char[count + 1];
	is.read(readed, count * sizeof(char));
	readed[count] = '\0';

	for (size_t i = 0; i < count; i++)
		readed[i] = tolower(readed[i]);

	return readed;
}

static void getNextChar(ifstream& is, char& destination)
{
	unsigned long long currentPos = is.tellg();
	destination = tolower(is.get());
	is.seekg(-1, std::ios::cur);
}

static char* getBestMatch(const Trie& trie, char* phrase, ifstream& is)
{
	char nextChar;
	getNextChar(is, nextChar);

	int phraseLen = strlen(phrase);
	for (size_t i = 0; i < phraseLen; i++)
	{
		// If the next char is not a letter we hit a valid phrase!
		if (!isLetter(nextChar))
		{
			// check if trie contains the word [0, phraseLen - i - 1]
			char* substr = new char[phraseLen - i + 1];
			strncpy(substr, phrase, phraseLen - i);
			substr[phraseLen - i] = '\0';

			if (trie.contains(substr))
				return substr;

			delete[] substr;
		}

		nextChar = phrase[phraseLen - i - 1];
	}

	return "";
}

static int getWordsCount(const char* fileName)
{
	ifstream is(fileName);
	int wordCount = 0;
	int fileLenght = getContentLength(is);
	int currentIndex = 0;

	bool isPreviousALetter = false;
	bool isLetterEverFound = false;
	
	while (currentIndex < fileLenght)
	{
		int maxCharsToRead = currentIndex + 1024 < fileLenght ?
			1024 :
			fileLenght - currentIndex;

		char* buffer = new char[maxCharsToRead + 1];
		is.read(buffer, maxCharsToRead);
		buffer[maxCharsToRead] = '\0';

		for (size_t i = 0; i < maxCharsToRead; i++)
		{
			if (!isLetter(tolower(buffer[i])) && isPreviousALetter)
				wordCount++;

			if (isLetter(tolower(buffer[i])))
				isLetterEverFound = true;

			isPreviousALetter = isLetter(tolower(buffer[i])) ? true : false;
		}

		currentIndex += maxCharsToRead;
		delete[] buffer;
	}

	if (isPreviousALetter || (isLetterEverFound && wordCount == 0))
		wordCount++;

	is.close();
	return wordCount;
}

bool isNumber(char* str)
{
	int stringLen = strlen(str);
	int i = 0;

	if (str[0] == '-')
		i = 1;

	for (; i < stringLen; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}

	return true;
}

void fillTheTrieAndGetMaxLenght(Trie& trie, char* dictionaryFileName, int& maxWordLength)
{
	ifstream is(dictionaryFileName);

	maxWordLength = -1;

	char currentWord[4096] = "";
	char buffer[2048];
	is >> buffer;

	while (true)
	{
		if (!strlen(buffer))
			break;

		if (isNumber(buffer))
		{
			int currentPhraseLen = strlen(currentWord);
			if (currentPhraseLen > maxWordLength)
				maxWordLength = currentPhraseLen;

			trie.add(currentWord, atoi(buffer));
			currentWord[0] = '\0';

			is >> buffer;
		}
		else
		{
				strcat(currentWord, buffer);

				// If the phrase continue we need to add space
				is >> buffer;

				if (!isNumber(buffer))
					strcat(currentWord, " ");
		}
	}

	is.close();
}

int main(int argc, char* argv[])
{
	Trie trie;
	int maxWordLength;
	fillTheTrieAndGetMaxLenght(trie, argv[1], maxWordLength);

	int filesCount = argc - 2;

	for (size_t i = 0; i < filesCount; i++)
	{
		ifstream is(argv[i + 2]);
		unsigned long long contentLenght = getContentLength(is);
		unsigned long long currentStreamIndex = 0;
		double totalScore = 0.0;
		bool isAnyWordFound = false;

		while (currentStreamIndex < contentLenght)
		{
			int maxCanRead = currentStreamIndex + maxWordLength <= contentLenght ?
				maxWordLength :
				contentLenght - currentStreamIndex;

			char* currentPhrase = readChars(maxCanRead, is);
			char* match = getBestMatch(trie, currentPhrase, is);

			int currentPhraseLen = strlen(currentPhrase);

			// If we didnt hit anything we will set the stream pointer the to start of the next word
			if (!strlen(match))
			{
				for (size_t i = 0; i < currentPhraseLen; i++)
				{
					if (isLetter(tolower(currentPhrase[i])))
						currentStreamIndex++;
					else
						break;
				}

				currentStreamIndex++;

				unsigned long long currentIndex = (unsigned long long)is.tellg();

				// reached end of the file 
				if (currentIndex == -1) 
				{
					is.clear();
					is.seekg(currentStreamIndex - contentLenght, std::ios::end);
				}
				else
				{
					is.seekg(currentStreamIndex - currentIndex, std::ios::cur);
				}
			}
			// If we found match we will move the pointer where the founded match end.
			// That way we are sure that we select the longest one with the same prefix (if exist)
			else
			{
				int matchLen = strlen(match);
				isAnyWordFound = true;
				totalScore += trie.getScore(match);
				currentStreamIndex += matchLen + 1;
				is.seekg((int)(matchLen - currentPhraseLen + 1), std::ios::cur);
				delete[] match;
			}

			delete[] currentPhrase;
		}

		is.close();

		if (isAnyWordFound)
			cout << argv[i + 2] << " " << totalScore / getWordsCount(argv[i + 2]) << endl;
		else
			cout << argv[i + 2] << " 0" << endl;
	}

	system("pause");
	return 0;
}