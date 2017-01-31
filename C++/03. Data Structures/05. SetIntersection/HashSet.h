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

#ifndef __HASH_SET_HEADER_INCLUDED__
#define __HASH_SET_HEADER_INCLUDED__

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long uint_64;

// This class is optimized for the current homework task and it is not generic implementation.
// This class only works with 64 bit non-negative integers, and uses open adressing
// Some methods like remove, etc which this task arent used, are also not implemented also isnt not handling re-sizing.
class HashSet
{
private:

	uint_64* data;
	int capacity;
	int size;

	const static int PRIME_FACTOR = 137;
	const static int INITIAL_VALUE = 0;

	const static uint_64 FNV_PRIME = 1099511628211;
	const static uint_64 FNV_OFFSET = 14695981039346656037;

	// http://isthe.com/chongo/tech/comp/fnv/#FNV-1a
	int hashCode(uint_64 n)
	{
		uint_64 hash = FNV_OFFSET;

		for (size_t i = 0; i < 8; i++)
		{
			// i-th octet (8 bits)
			uint_64 byte = n & (0xFF << (8 * i));

			hash ^= byte;
			hash *= FNV_PRIME;
		}

		return hash % capacity;
	}

public:

	HashSet(int initialSize = 10) : size(0), capacity(initialSize)
	{
		data = new uint_64[capacity];

		for (int i = 0; i < capacity; ++i)
			data[i] = INITIAL_VALUE;
	};

	~HashSet() { delete[] data; };

	HashSet& operator=(const HashSet& rhs)
	{
		if (this == &rhs)
			return *this;

		if (capacity != rhs.capacity)
		{
			delete[] data;
			data = new uint_64[rhs.capacity];
			capacity = rhs.capacity;
		}

		size = rhs.size;

		for (int i = 0; i < capacity; ++i)
			data[i] = rhs.data[i];

		return *this;
	}

	void add(uint_64 n)
	{
		int hash = hashCode(n);

		while (data[hash] != INITIAL_VALUE)
		{
			// If the key already is added
			if (data[hash] == n)
				break;

			hash = (hash + PRIME_FACTOR) % capacity;
		}

		size++;
		data[hash] = n;
	}

	bool contains(uint_64 n)
	{
		int hash = hashCode(n);

		while (data[hash] != INITIAL_VALUE)
		{
			if (data[hash] == n)
				return true;
			else
				hash = (hash + PRIME_FACTOR) % capacity;
		}

		return false;
	}

	void print() const
	{
		cout << "Printing.." << endl;

		for (int i = 0; i < capacity; ++i)
		{
			if (data[i] != INITIAL_VALUE)
				cout << data[i] << endl;
		}

		cout << "Done.." << endl;
	}

	void serializeToFile(const char* fileName) const
	{
		ofstream of(fileName);

		for (int i = 0; i < capacity; ++i)
		{
			if (data[i] != INITIAL_VALUE)
				of.write((char*)&data[i], sizeof(uint_64));
		}

		of.close();
	}

	bool isEmpty() const
	{
		return getSize() == 0;
	}

	int getSize() const
	{
		return size;
	}

	int getCapacity() const
	{
		return capacity;
	}
};

#endif
