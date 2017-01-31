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
#ifndef __TRIE_HEADER_INCLUDED__
#define __TRIE_HEADER_INCLUDED__

#include <iostream>

using std::nothrow;

class Trie
{
private:

	struct node
	{
		// 0-26		correspond to a-z
		// 27		correspond to ' ', '\t', '\r', '\n'
		static const int MAX_CHARS = 27;

		node** siblings;
		int score;
		bool isEnd;

		void allocateSiblings(node**& siblings)
		{
			this->siblings = new (nothrow) node*[MAX_CHARS];

			if (!this->siblings)
				throw "Cannot allocate enough memory for the sibling nodes";

			for (size_t i = 0; i < MAX_CHARS; i++)
				this->siblings[i] = nullptr;
		}

		node(bool isEnd = false, int score = 0)
		{
			this->isEnd = isEnd;
			this->score = score;
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
	};

	node* head;

public:

	Trie() { this->head = new node(); }

	~Trie() { delete head; }

	bool contains(const char* phrase) const;

	void add(const char* phrase, int score);

	int getScore(const char* phrase) const;
};


#endif