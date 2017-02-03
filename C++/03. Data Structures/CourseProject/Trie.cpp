/**
*
* Solution to course project
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Georgiev
* @idnumber 45115
* @task course project
* @compiler VC
*
*/
#include "Trie.h"

bool getBitIndex(char bit) { return bit - '0'; }

bool Trie::contains(const char * bits) const
{
	int len = strlen(bits);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		bool bitIndex = getBitIndex(bits[i]);

		if (!currentNode->siblings[bitIndex])
			return false;

		currentNode = currentNode->siblings[bitIndex];
	}

	return currentNode->isEnd;
}

void Trie::add(const char * bits, unsigned char code)
{
	int len = strlen(bits);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		bool bitIndex = getBitIndex(bits[i]);

		if (!currentNode->siblings[bitIndex])
			currentNode->siblings[bitIndex] = new node();

		currentNode = currentNode->siblings[bitIndex];
	}

	currentNode->isEnd = true;
	currentNode->code = (short)code;
}

unsigned char Trie::getCode(const char* bits) const
{
	int len = strlen(bits);

	node* currentNode = head;
	for (size_t i = 0; i < len; i++)
	{
		currentNode = currentNode->siblings[getBitIndex(bits[i])];

		if (!currentNode)
			throw "Bit representation not found";
	}

	return currentNode->code;
}

bool Trie::deserializeHeaderToTrie(std::ifstream& is)
{
	unsigned short headerLen;
	is.read((char*)&headerLen, sizeof(headerLen));

	if (!headerLen)
		return false;

	// Iterate over the codes and add them in the trie
	int readedBytes = 0;
	while (readedBytes != headerLen)
	{
		unsigned char bitsCount;
		is.read((char*)&bitsCount, sizeof(bitsCount));

		char* bits = new char[(int)bitsCount + 1];
		is.read((char*)bits, bitsCount * sizeof(char));
		bits[(int)bitsCount] = '\0';

		unsigned char code;
		is.read((char*)&code, sizeof(code));

		this->add((char*)bits, code);

		// Increment the bits lenght + 1 character for the code + 1 for bits count
		readedBytes += ((int)bitsCount) + 2;

		delete[] bits;
	}

	return true;
}

void Trie::deserializeFile(std::ifstream & is, std::ofstream & os)
{
	// Create trie from the header
	if (!deserializeHeaderToTrie(is))
		return;

	unsigned long long contentInBits = 0;
	is.read((char*)&contentInBits, sizeof(contentInBits));

	if (!contentInBits)
		return;

	// Saving the current position in the input stream
	// that is just before the actual content
	unsigned long long currentPosInStream = is.tellg();

	is.seekg(0, std::ios::end);
	unsigned long long fileSize = is.tellg();
	
	if (currentPosInStream == fileSize)
		return;

	// Reset the position of the stream just before the content
	is.seekg(currentPosInStream, std::ios::beg);

	while (true)
	{
		currentPosInStream = is.tellg();

		// Calculate how many bytes can read from the input steam
		int bytesCanRead = currentPosInStream + READ_CHUNK_SIZE > fileSize ?
			fileSize - currentPosInStream :
			READ_CHUNK_SIZE;

		// Calculate how many bits can read. We need this calculation
		// because the bits are rounded by 2 bits, so the most right bits
		// may not be from the compression, so we dont need them
		int bitsToRead = bytesCanRead * 8 < contentInBits ?
			bytesCanRead * 8 :
			contentInBits;

		if (!bitsToRead)
			break;

		contentInBits -= bitsToRead;

		unsigned int data;
		is.read((char*)&data, sizeof(data));
		
		for (int i = 0; i < bitsToRead; i++)
		{
			bool bit = data & (1 << 31 - i);

			searchPointer = searchPointer->siblings[bit];

			if (searchPointer->isEnd)
			{
				// Write the value to the output stream
				os.write((char*)&searchPointer->code, sizeof(searchPointer->code));
				// Reset the search pointer to the head
				searchPointer = head;
			}
		}
	}

	// If the search pointer is not pointing the root when the
	// decompression ends, that means the compressed data is not full or corrupted
	if (head != searchPointer)
		throw "Invalid compressed data";
}