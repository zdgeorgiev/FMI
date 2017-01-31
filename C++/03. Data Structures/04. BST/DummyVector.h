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

#ifndef __DUMMY_VECTORE_HEADER_INCLUDED__
#define __DUMMY_VECTORE_HEADER_INCLUDED__

#include "KVPair.h"

// Requirements for T are that the operator < is mandatory!
template<typename T>
class DummyVector
{
private:

	T* data;
	int size;
	int capacity;

	void resizeDouble()
	{
		capacity *= 2;

		T* newData =  new (std::nothrow) T[capacity];

		if (!newData)
			throw "Cannot alocate enough memory for the container";

		for (size_t i = 0; i < size; i++)
			newData[i] = data[i];

		delete data;
		data = newData;
	}

	void mergeSort()
	{
		if (size <= 1)
			return;

		T* newData = new (std::nothrow) T[capacity];

		topDownSplit(0, this->size - 1, newData);

		delete[] data;

		data = newData;
	}

	void topDownSplit(int start, int end, T* destination)
	{
		if (end - start < 1)
			return;

		int mid = (start + end) / 2;
		topDownSplit(start, mid, destination);
		topDownSplit(mid + 1, end, destination);
		merge(start, end, destination);
	}

	void merge(int start, int end, T* destination)
	{
		int mid = (end + start) / 2;
		int leftIndex = start;
		int rightIndex = mid + 1;
		int currentIndex = start;

		while (leftIndex <= mid && rightIndex <= end)
		{
			if (this->data[leftIndex] < this->data[rightIndex])
			{
				destination[currentIndex] = this->data[leftIndex];
				leftIndex++;
			}
			else
			{
				destination[currentIndex] = this->data[rightIndex];
				rightIndex++;
			}

			currentIndex++;
		}

		while (rightIndex <= end)
		{
			destination[currentIndex] = this->data[rightIndex];
			currentIndex++;
			rightIndex++;
		}

		while (leftIndex <= mid)
		{
			destination[currentIndex] = this->data[leftIndex];
			currentIndex++;
			leftIndex++;
		}

		for (int k = start; k <= end; k++)
			this->data[k] = destination[k];
	}

public:

	DummyVector() : size(0), capacity(2)
	{
		data = new (std::nothrow) T[capacity];

		if (!data)
			throw "Cannot alocate enough memory for the container";
	}

	~DummyVector()
	{
		delete[] data;
	}

	T& operator[](int index) const
	{
		return data[index];
	}

	void add(const T& key)
	{
		if (size == capacity)
			resizeDouble();

		data[size] = key;
		size++;
	}

	int getSize() const
	{
		return size;
	}

	// Sort the vector using merge sort
	void sort()
	{
		mergeSort();
	}
};

#endif