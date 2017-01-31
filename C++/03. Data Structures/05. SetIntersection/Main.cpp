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

#include "HashSet.h"

using namespace std;

typedef unsigned long long uint_64;

char** readFilesFromStdOut(int filesCount);
char* getSmallestFile(char** files, int fileCount);
HashSet* initialize(char* file);

int main()
{
	int filesCount;
	cin >> filesCount;

	if (filesCount == 0)
		return 0;

	cin.ignore();

	char** files = readFilesFromStdOut(filesCount);
	char* smallestFile = getSmallestFile(files, filesCount);

	HashSet* hs = initialize(smallestFile);

	for (int i = 0; i < filesCount; ++i)
	{
		char* currentFile = files[i];

		// skip the smallest file
		if (!strcmp(currentFile, smallestFile))
			continue;

		HashSet* intersection = new HashSet(hs->getCapacity());

		ifstream is(currentFile);

		while (true)
		{
			uint_64 n;
			is.read((char*)&n, sizeof(uint_64));

			if (is.eof())
				break;

			if (hs->contains(n))
				intersection->add(n);
		}

		is.close();

		// If at some point the intersection is empty
		// we no longer have to check the other files
		if (intersection->isEmpty())
			break;

		delete hs;

		// Swap the previous intersection with the new one
		hs = intersection;
	}

	// Write the output in binary file
	hs->serializeToFile("result.bin");

	delete hs;

	for (int i = 0; i < filesCount; ++i)
		delete[] files[i];
	delete[] files;

	delete[] smallestFile;

	system("pause");
	return 0;
};

char** readFilesFromStdOut(int filesCount)
{
	char** files = new char*[filesCount];

	for (int i = 0; i < filesCount; ++i)
	{
		char buffer[1024];
		cin.getline(buffer, 1024);
		files[i] = new char[strlen(buffer) + 1];
		strcpy(files[i], buffer);
	}

	return files;
}

char* getSmallestFile(char** files, int fileCount)
{
	char* smallestFile = new char[1024];
	uint_64 minSize = 1 << 32 - 1;

	for (int i = 0; i < fileCount; ++i)
	{
		ifstream f(files[i]);
		f.seekg(0, ios_base::end);
		uint_64 currentFileSize = f.tellg();
		f.close();

		if (minSize > currentFileSize)
		{
			minSize = currentFileSize;
			strcpy(smallestFile, files[i]);
		}
	}

	return smallestFile;
}

// Create hash set from the numbers in given file.
// Hash set initial size will be the first power of 2 which is bigger than numbers in the file + 10% free space.
// That way we will keep the hash set at most 90% full and wont make any resizes.
HashSet* initialize(char* file)
{
	ifstream is(file);
	is.seekg(0, ios_base::end);
	uint_64 numbersCount = is.tellg() / sizeof(uint_64);
	is.clear();
	is.seekg(0, ios_base::beg);

	// add the 10% free space
	numbersCount += numbersCount / 10;

	unsigned int firstPowerOf2 = 1024;
	while (firstPowerOf2 < numbersCount)
		firstPowerOf2 <<= 1;

	HashSet* set = new HashSet(firstPowerOf2);

	while (true)
	{
		uint_64 n;
		is.read((char*)&n, sizeof(uint_64));

		if (is.eof())
			break;

		set->add(n);
	}

	is.close();

	return set;
}