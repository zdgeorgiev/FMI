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
#pragma once

#ifndef __HUFFMAN_TREE_HEADER_INCLUDED__
#define __HUFFMAN_TREE_HEADER_INCLUDED__

#include <fstream>

class HuffmanTree
{
private:

	static const int LEAFS_COUNT = 256;
	static const int NODES_CAPACITY = 2 * LEAFS_COUNT - 1;

	static const int READ_CHUNK_SIZE = 4096;

	struct node
	{
		node* left;
		node* right;
		int occurrence;
		short symbol;

		node(node* left = nullptr, node* right = nullptr, int occurrence = 0, short symbol = 0)
		{
			this->left = left;
			this->right = right;
			this->occurrence = occurrence;
			this->symbol = symbol;
		}

		~node()
		{
			if (!left) delete left;
			if (!right) delete right;
		}

		bool isLeaf() { return left == nullptr && right == nullptr; }
	};

	node* root;

	// After building the tree this matrix contains
	// the bit representation of the i-th character.
	// The second dimension is NODES_LEAFS - 1, because
	// in the worst case one symbol can have NODES_LEAFS - 1 bits.
	char* bitMap[LEAFS_COUNT - 1];

	// This variable holds how many nodes left unmerged in the histogram.
	int notMergedNodes = 0;

	// Build part triggers the creation of the histogram
	// and then create the tree by merging the lowest two
	// nodes by occurrences in the input stream.
	void buildTree(std::ifstream& is);

	// Creates histogram with size of NODES_CAPACITY nodes.
	// This is because we will keep all the nodes in this array.
	// That includes the new nodes that will be added.
	// In the worst case the tree height will be 2 * LEAFS_COUNT - 1.
	node* createHistogram(std::ifstream& is, unsigned long long contentSize);

	// Recursively traversing the nodes in top-bottom approach and writing
	// the path in the @bits char array. 0 for the left child, 1 for the right.
	void serializeLeafs(node* root, char* bits, int level, std::ofstream & os);

public:

	HuffmanTree() { root = new node(); }

	~HuffmanTree() { delete root; }

	/// Creates HuffmanTree from input stream that points to the content a file
	HuffmanTree(std::ifstream& is) : HuffmanTree() { buildTree(is); }

	/// Serialize the huffman tree in the following schema
	/// [DictionaryLenBytes] => 2 bytes
	/// For each element
	/// [BitsLen] => 1 byte
	/// [BitsCode] => BitsLen * sizeof(char)
	/// [Code] => 1 byte
	void serialize(std::ifstream& is, std::ofstream& os);
};

#endif