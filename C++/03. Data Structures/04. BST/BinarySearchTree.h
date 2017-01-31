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
#pragma once

#ifndef __BINARY_SEARCH_TREE_HEADER_INCLUDED__
#define __BINARY_SEARCH_TREE_HEADER_INCLUDED__

#include <iostream>

// This class is copied from Peter Armqnov.
// Unnecessery code is removed and it is modified to handle the task requirements.
// Requirements for T is that the operators ==, <, > are mandatory!. <, > are used for only Key compare
template<typename T>
class BinarySearchTree
{
private:

	struct node
	{
		T data;
		node *left, *right;

		node(const T& data, node* left = nullptr, node* right = nullptr)
			: data(data)
			, left(left)
			, right(right)
		{
		}
	};

	node* root;
	int size;

	void insert(node*& root, T& key)
	{
		if (!root)
			root = new node(key);
		else
			insert(key < root->data ? root->left : root->right, key);
	}

	bool remove(node*& root, const T& key)
	{
		if (!root) return false;
		if (root->data == key)
		{
			node* toDel = root;
			if (!root->left)
			{
				root = root->right;
			}
			else if (!root->right)
			{
				root = root->left;
			}
			else
			{
				node* mR = extractMin(root->right);
				mR->left = root->left;
				mR->right = root->right;
				root = mR;
			}
			size--;
			delete toDel;
			return true;
		}
		else
		{
			remove(key < root->data ? root->left : root->right, key);
		}
	}

	int removeByKey(node*& root, const T& key)
	{
		if (!root) return false;
		// Its equal (only for key compare)
		if (!(root->data < key) && !(root->data > key))
		{
			node* toDel = root;
			if (!root->left)
			{
				root = root->right;
			}
			else if (!root->right)
			{
				root = root->left;
			}
			else
			{
				node* mR = extractMin(root->right);
				mR->left = root->left;
				mR->right = root->right;
				root = mR;
			}
			size--;
			delete toDel;
			return true;
		}
		else
		{
			removeByKey(key < root->data ? root->left : root->right, key);
		}
	}

	bool contains(const node* root, const T& key) const
	{
		if (!root) return false;
		if (root->data == key) return true;
		return key < root->data ? contains(root->left, key) : contains(root->right, key);
	}

	node* extractMin(node*& root)
	{
		if (root->left)
			return extractMin(root->left);

		node* n = root;
		root = root->right;
		return n;
	}

	void clear(node* root)
	{
		if (!root)
			return;

		clear(root->left);
		clear(root->right);
		delete root;
	}

public:
	BinarySearchTree() : root(nullptr), size(0) { };

	~BinarySearchTree() { clear(root); }

	void insert(T& key)
	{ 
		insert(root, key);
		size++;
	}

	bool remove(const T& key)
	{
		return remove(root, key);
	}

	int removeAll(const T& key)
	{
		int count = 0;

		while (removeByKey(root, key))
			count++;

		return count;
	}

	bool contains(const T& key) const
	{
		return contains(root, key);
	}

	int getSize() const
	{
		return size;
	}
};

#endif