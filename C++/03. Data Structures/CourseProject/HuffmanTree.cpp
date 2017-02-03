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
#include "HuffmanTree.h"

void HuffmanTree::buildTree(std::ifstream& is)
{
	is.seekg(0, std::ios::end);
	unsigned long long contentSize;
	contentSize = is.tellg() / sizeof(char);
	is.seekg(0, std::ios::beg);

	if (!contentSize)
		return;

	node* nodes = createHistogram(is, contentSize);

	// This variable will be used as a index where to add
	// the new node that merges the lowest two nodes.
	// Merge nodes will be added in the first available cell
	int nextMergeIndex = LEAFS_COUNT + 0;

	while (notMergedNodes != 1)
	{
		node* lowest2 = new node[2];

		// Using selection sort the get the first 2 lowest 
		// nodes selected by occurrunce in the input stream
		for (int i = 0; i < 2; i++)
		{
			unsigned int minOccurrs = -1;

			for (int currentNode = 0; currentNode < NODES_CAPACITY; currentNode++)
			{
				if (nodes[currentNode].occurrence != 0 &&
					nodes[currentNode].occurrence <= minOccurrs)
				{
					// We dont want to get the lowest node twice
					if (i == 1 && nodes[currentNode].symbol == lowest2[0].symbol)
						continue;

					minOccurrs = nodes[currentNode].occurrence;

					lowest2[i].left = nodes[currentNode].left;
					lowest2[i].right = nodes[currentNode].right;
					lowest2[i].occurrence = nodes[currentNode].occurrence;
					lowest2[i].symbol = nodes[currentNode].symbol;
				}
			}
		}

		nodes[nextMergeIndex].left = &lowest2[0];
		nodes[nextMergeIndex].right = &lowest2[1];
		nodes[nextMergeIndex].occurrence = lowest2[0].occurrence + lowest2[1].occurrence;
		nodes[nextMergeIndex].symbol = nextMergeIndex;

		// Reset the occurrences for the already merged nodes
		// to prevent from picking up them again
		nodes[lowest2[0].symbol].occurrence = 0;
		nodes[lowest2[1].symbol].occurrence = 0;

		// On every step we merge two nodes in new one
		notMergedNodes--;
		// Increment the next merged node index
		nextMergeIndex++;
	}

	// If we merged atleast two nodes
	if (nextMergeIndex > 256)
	{
		*root = nodes[nextMergeIndex - 1];
	}
	else
	{
		// Else we need to find the only one node
		// that is in the histogram and add it to the root
		for (int i = 0; i < NODES_CAPACITY; i++)
		{
			if (nodes[i].occurrence != 0)
			{
				root->left = &nodes[(unsigned char)nodes[i].symbol];
				root->right = new node();
				break;
			}
		}
	}
}

HuffmanTree::node* HuffmanTree::createHistogram(std::ifstream& is, unsigned long long contentSize)
{
	node* histogram = new node[NODES_CAPACITY];
	for (int i = 0; i < LEAFS_COUNT; i++)
		histogram[i].symbol = (unsigned char)i;

	unsigned long long currentByte = 0;
	while (true)
	{
		int bytesToRead = currentByte + READ_CHUNK_SIZE > contentSize ?
			contentSize - currentByte :
			READ_CHUNK_SIZE;

		currentByte += bytesToRead;

		if (!bytesToRead)
			break;

		unsigned char* chunk = new unsigned char[bytesToRead + 1];
		is.read((char*)chunk, bytesToRead * sizeof(char));
		chunk[bytesToRead] = '\0';

		for (int j = 0; j < bytesToRead; j++)
		{
			// Increment the nodes count for unique ones
			notMergedNodes += histogram[chunk[j]].occurrence == 0 ? 1 : 0;
			histogram[chunk[j]].occurrence++;
		}
	}

	// Reset the pointer to the content
	is.seekg(0, std::ios::beg);

	return histogram;
}

void HuffmanTree::serialize(std::ifstream& is, std::ofstream& os)
{
	long long headerBegPos = os.tellp();

	// Leave space for the header bytes len
	unsigned short headerLen = 0;
	os.write((char*)&headerLen, sizeof(headerLen));

	unsigned long long fileSize;
	is.seekg(0, std::ios::end);
	fileSize = is.tellg();
	is.seekg(0, std::ios::beg);

	if (!fileSize)
		return;

	long long contentBegPos = os.tellp();

	char* bits = new char[LEAFS_COUNT];
	serializeLeafs(this->root, bits, 0, os);
	delete[] bits;

	// Write the header bytes len
	headerLen = (os.tellp() - contentBegPos) / sizeof(char);
	os.seekp(((long long)os.tellp() - headerBegPos) * -1, std::ios::cur);
	os.write((char*)&headerLen, sizeof(headerLen));
	os.seekp(0, std::ios::end);

	long long bitsLenBegPos = os.tellp();

	// Leave space for the serialized bits len
	unsigned long long serializedBits = 0;
	os.write((char*)&serializedBits, sizeof(serializedBits));

	unsigned long long currentPosInStream = 0;

	int bitPos = 0;
	unsigned long long bitsTotal = 0;
	unsigned int data = 0;
	
	// Write the content using the codes table
	while (true)
	{
		int bytesCanRead = currentPosInStream + READ_CHUNK_SIZE > fileSize ?
			fileSize - currentPosInStream :
			READ_CHUNK_SIZE;

		currentPosInStream += bytesCanRead;

		if (!bytesCanRead)
			break;

		unsigned char* chunk = new unsigned char[bytesCanRead + 1];
		is.read((char*)chunk, bytesCanRead * sizeof(char));
		chunk[bytesCanRead] = '\0';

		for (int i = 0; i < bytesCanRead; i++)
		{
			// Get the current char and write its bits from the bit map
			int bitsLen = strlen(bitMap[chunk[i]]);
			bitsTotal += bitsLen;

			for (int bitIndex = 0; bitIndex < bitsLen; bitIndex++)
			{
				bool bit = bitMap[chunk[i]][bitIndex] == '1' ? 1 : 0;

				// Write the bit in the next available cell
				data |= (unsigned int)(bit << sizeof(data) * 8 - 1 - bitPos);

				bitPos++;

				// When all bits are complete, the data is writen in the os
				if (bitPos == sizeof(data) * 8)
				{
					os.write((char*)&data, sizeof(data));
					data = 0;
					bitPos = 0;
				}
			}
		}
	}

	// We have to write the last 4 bytes
	if (bitPos > 0)
		os.write((char*)&data, sizeof(data));

	// Write the content len in bits
	os.seekp((os.tellp() - bitsLenBegPos) * -1, std::ios::end);
	os.write((char*)&bitsTotal, sizeof(bitsTotal));
	os.seekp(0, std::ios::end);
}

void HuffmanTree::serializeLeafs(node* root, char* bits, int level, std::ofstream & os)
{
	if (root->isLeaf())
	{
		bits[level] = '\0';
		os.write((char*)&level, sizeof(char));
		os.write(bits, sizeof(char) * level);
		os.write((char*)&root->symbol, sizeof(unsigned char));
		bitMap[(unsigned char)root->symbol] = new char[level];
		strcpy(bitMap[(unsigned char)root->symbol], bits);
		return;
	}

	bits[level] = '0';
	serializeLeafs(root->left, bits, level + 1, os);
	bits[level] = '1';
	serializeLeafs(root->right, bits, level + 1, os);
}