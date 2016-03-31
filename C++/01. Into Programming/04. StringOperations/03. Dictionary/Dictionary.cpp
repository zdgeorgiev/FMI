#include <iostream>

int main()
{
	int n;
	std::cin >> n;

	char** dictionary = new (std::nothrow)char*[n + 1];
	if (!dictionary)
	{
		return 1;
	}
	
	for (size_t i = 0; i < n; i++)
	{
		dictionary[i] = new (std::nothrow)char[16];
		if (!dictionary[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete[] dictionary[j];
			}
			delete[] dictionary;
			return 1;
		}
	}

	std::cin.sync();

	for (size_t i = 0; i < n; i++)
	{
		//Read each word
		char currentWord[16] = { 0 };
		std::cin.getline(currentWord, 16);

		for (size_t j = 0; j < 16; j++)
		{
			if (currentWord[j] == ' ')
			{
				break;
			}

			dictionary[i][j] = currentWord[j];
		}
	}

	dictionary[n] = '\0';

	char buffer[1024];
	std::cin.getline(buffer, 1024);
	int lengthOfInput = strlen(buffer);

	char* reversedWords = new (std::nothrow)char[lengthOfInput + 1];

	if (!reversedWords)
	{
		return 1;
	}

	char* token;
	token = strtok(buffer, " ");
	int index = 0;

	//Processing each splitted substring
	while (true)
	{
		if (token == NULL)
		{
			//Delete the last white space and also end the string
			reversedWords[index - 1] = '\0';
			break;
		}

		for (size_t i = 0; i < n; i++)
		{
			bool areEqual = true;
			int currentWordLength = strlen(dictionary[i]);

			for (size_t j = 0; j < currentWordLength; j++)
			{
				if (dictionary[i][j] != token[j])
				{
					areEqual = false;
				}
			}

			if (areEqual)
			{
				//Add reversed word to the new array
				for (size_t k = 0; k < currentWordLength; k++)
				{
					reversedWords[index] = dictionary[i][currentWordLength - 1 - k];
					index++;
				}

				reversedWords[index] = ' ';
				index++;

				break;
			}
		}

		token = strtok(NULL, " ");
	}

	int resultLength = strlen(reversedWords);
	std::cout << "Result - " << reversedWords << std::endl;
	std::cout << "Length - " << resultLength << std::endl;

	for (size_t i = 0; i < n; i++)
	{
		delete[] dictionary[i];
	}
	delete[] dictionary;
	delete[] reversedWords;

	return 0;
}