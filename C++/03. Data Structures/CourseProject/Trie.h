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

#ifndef __TRIE_HEADER_INCLUDED__
#define __TRIE_HEADER_INCLUDED__

#include <fstream>

class Trie
{
private:

	static const int READ_CHUNK_SIZE = sizeof(int);

	struct node
	{
		// We only keep the bits ( 0 - 1 )
		static const int MAX_CHARS = 2;

		node** siblings;
		bool isEnd;

		// Code represent the extended ASCII symbol ( 0 - 255 )
		unsigned char code;

		node(bool isEnd = false, unsigned char code = 0)
		{
			this->isEnd = isEnd;
			this->code = code;
			allocateSiblings(this->siblings);
		}

		~node()
		{
			for (size_t i = 0; i < this->MAX_CHARS; i++)
			{
				if (this->siblings[i])
					delete this->siblings[i];
			}
			delete[] this->siblings;
		}

		void allocateSiblings(node**& siblings)
		{
			this->siblings = new (std::nothrow) node*[MAX_CHARS];

			if (!this->siblings)
				throw "Cannot allocate enough memory for the sibling nodes";

			for (size_t i = 0; i < MAX_CHARS; i++)
				this->siblings[i] = nullptr;
		}
	};

	node* head;

	// This pointer is used when searching in the trie.
	// This pointer is reset to root when a found occurr. In the current
	// use of this trie we know that serialized content bits
	// always represent something in the trie.
	node* searchPointer;

	// Deserialize file header to valid trie from intput stream
	// File header schema is :
	// [DictionaryLenBytes] => 2 bytes
	// For each element
	// [BitsLen] => 1 byte
	// [BitsCode] => BitsLen * sizeof(char)
	// [Code] => 1 byte
	//
	// Returns @true if deserializing the trie is successful or
	//		   @false if the content is empty
	bool deserializeHeaderToTrie(std::ifstream& is);

public:

	Trie() { this->head = new node(); this->searchPointer = head; }

	~Trie() { delete head; }

	bool contains(const char* bits) const;

	void add(const char* bits, unsigned char code);

	unsigned char getCode(const char* bits) const;

	/// Deserialize file from input stream to output stream.
	/// This method first deserialize the file header to valid trie
	/// and then perform the writing the content to the output stream.
	void deserializeFile(std::ifstream& is, std::ofstream& os);
};


#endif