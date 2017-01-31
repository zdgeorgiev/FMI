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
#include "Trie.h"
#include <iostream>

bool isLetter(char c)
{
	return c >= 'a' && c <= 'z';
}

int getCharIndex(char c)
{
	if (isLetter(c)) return c - 'a';
	else if (c == '\n' || c == '\r' || c == '\t' || c == ' ') return 26;
	else return -1;
}

bool Trie::contains(const char * phrase) const
{
	int len = strlen(phrase);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		int letterIndex = getCharIndex(tolower(phrase[i]));

		if (letterIndex == -1 || !currentNode->siblings[letterIndex])
			return false;

		currentNode = currentNode->siblings[letterIndex];
	}

	return currentNode->isEnd;
}

void Trie::add(const char * phrase, int score)
{
	int len = strlen(phrase);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		int letterIndex = getCharIndex(tolower(phrase[i]));

		if (!currentNode->siblings[letterIndex])
			currentNode->siblings[letterIndex] = new node();

		currentNode = currentNode->siblings[letterIndex];
	}

	currentNode->isEnd = true;
	currentNode->score = score;
}

int Trie::getScore(const char * phrase) const
{
	int len = strlen(phrase);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		int letterIndex = getCharIndex(tolower(phrase[i]));
		currentNode = currentNode->siblings[letterIndex];
	}

	return currentNode->score;
}