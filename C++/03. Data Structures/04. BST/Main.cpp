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

#include "BinarySearchTree.h"
#include "DummyVector.h"
#include "KVPair.h"

using namespace std;

typedef DummyVector<KVPair> Vector;
typedef BinarySearchTree<KVPair> BST;

Vector* initializeFromFile(char* fileName);
void balancedAdd(const Vector& v, BST& bst);
void recursiveAdd(int start, int end, int size, const Vector& v, BST& bst);

int main(int argc, char* argv[])
{
	if (argc < 2)
		return -1;

	Vector* vector = initializeFromFile(argv[1]);

	vector->sort();

	BST bst;

	balancedAdd(*vector, bst);

	// Commands interface
	while (true)
	{
		char command[1024];

		cin >> command;

		if (cin.eof())
			break;

		if (!strcmp(command, "add"))
		{
			cin >> command;
			int key = atoi(command);
			cin >> command;
			bst.insert(KVPair(key, command));
		}
		else if (!strcmp(command, "remove"))
		{
			cin >> command;
			int key = atoi(command);
			cin >> command;
			cout << (bst.remove(KVPair(key, command)) ? "true" : "false") << endl;
		}
		else if (!strcmp(command, "removeall"))
		{
			cin >> command;
			int key = atoi(command);
			cout << bst.removeAll(KVPair(key, "")) << endl;
		}
		else if (!strcmp(command, "search"))
		{
			cin >> command;
			int key = atoi(command);
			cin >> command;
			cout << (bst.contains(KVPair(key, command)) ? "true" : "false") << endl;
		}
	}

	delete vector;

	system("pause");
	return 0;
}

Vector* initializeFromFile(char* fileName)
{
	Vector* vector = new Vector();

	ifstream is(fileName);
	
	while (true)
	{
		if (is.peek() == -1)
			break;

		int key;
		is.read((char*)&key, sizeof(int));
		int valueLen;
		is.read((char*)&valueLen, sizeof(int));
		char* value = new char[valueLen + 1];
		is.read(value, valueLen);
		value[valueLen] = '\0';

		vector->add(KVPair(key, value));
	}

	is.close();

	return vector;
}

void balancedAdd(const Vector& source, BST& destination)
{
	int vectorSize = source.getSize();
	recursiveAdd(0, vectorSize, vectorSize, source, destination);
}

void recursiveAdd(int start, int end, int size, const Vector& v, BST& bst)
{
	if (start > end || start >= size)
		return;

	int mid = (end + start) / 2;
	bst.insert(v[mid]);
	recursiveAdd(start, mid - 1, size, v, bst);
	recursiveAdd(mid + 1, end, size, v, bst);
}