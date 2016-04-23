#include "BucketUtils.h"
#include <iostream>
#include <fstream>

using namespace std;

void createFileIfNotExist(const char* src)
{
	std::ofstream f(src, std::ios::app);
	f.close();
}

Bucket* BucketUtils::deserializeFromFile(const char * source)
{
	Bucket * loaded = new Bucket();

	ifstream s(source, std::ios::binary);

	if (!s)
		return NULL;

	// Read the owner name lenght
	int ownerNameLen;
	s.read((char*)&ownerNameLen, sizeof(int));

	// Read the owner name
	char ownerName[32];
	s.read((char*)&ownerName, sizeof(char) * ownerNameLen);
	memcpy((void*)(*loaded).getOwner(), ownerName, sizeof(char) * ownerNameLen);

	// Read the eggs in the container
	int eggsCount;
	s.read((char*)&eggsCount, sizeof(int));

	for (size_t i = 0; i < eggsCount; i++)
	{
		Egg e;

		// Read egg name
		char eggName[32];
		s.read((char*)eggName, sizeof(char) * 32);
		memcpy((void*)e.getName(), eggName, sizeof(char) * 32);

		// Read egg size
		int eggSize = 0;
		s.read((char*)&eggSize, sizeof(int));
		e.setSize(eggSize);

		// Add egg to the container
		(*loaded).addEgg(e);
	}

	return loaded;
}

void BucketUtils::serializeToFile(const Bucket & bucket, const char * destination)
{
	createFileIfNotExist(destination);

	ofstream s(destination, std::ios::binary | std::ios::trunc);
	
	if (!s)
		return;

	//Write the owner len + name
	int ownerLen = strlen(bucket.getOwner());
	s.write((char*)&ownerLen, sizeof(int));
	s.write((char*)bucket.getOwner(), ownerLen);

	//Write the container elements count
	int eggsInContainer = bucket.getElementsCount();
	s.write((const char*)&eggsInContainer, sizeof(int));

	for (size_t i = 0; i < eggsInContainer; i++)
	{
		s.clear();

		Egg currentEgg = bucket.getContainer()[i];

		//Write the name of the egg
		s.write((char*)currentEgg.getName(), 32);

		// Write the size of the egg
		int eggSize = currentEgg.getSize();
		s.write((char*)&eggSize, sizeof(int));
	}
}

void BucketUtils::createReport(const Bucket & bucket, ostream & os)
{
	for (size_t i = 0; i < bucket.getElementsCount(); i++)
	{
		const char* eggName = bucket.getContainer()[i].getName();
		int eggNameLen = strlen(eggName);

		os.write(eggName, eggNameLen);

		os.write(" ", 1);

		int eggSize = bucket.getContainer()[i].getSize();

		char asChar[100];
		_itoa(eggSize, asChar, 10);

		os.write((char*)&asChar, (log(eggSize) / log(10)) + 1);

		os.write("\n", 1);
	}
}
