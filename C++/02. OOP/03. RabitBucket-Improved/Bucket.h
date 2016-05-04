#pragma once

#ifndef _BUCKET_HEADER_INCLUDED_
#define _BUCKET_HEADER_INCLUDED_

#include "Egg.h"

class Bucket
{
public:
	Bucket(char* owner);
	Bucket();
	~Bucket();
	Bucket(const Bucket& rhs);

	Bucket& operator=(const Bucket& rhs);

	Egg& operator[](int index) const;
	Egg& operator[](char name[64]) const;

	Bucket operator%(const Bucket& rhs) const;
	Bucket& operator%=(const Bucket& rhs);

	Bucket operator+(const Bucket& rhs) const;
	Bucket& operator+=(const Bucket& rhs);

	friend char* operator+(const Bucket& v1, const Bucket& v2);
	friend Bucket& operator+=(Bucket& v1, const Bucket& v2);

	Bucket operator*(int size);
	Bucket& operator*=(int size) const;
	Bucket operator/(int size);
	Bucket& operator/=(int size) const;

	bool operator==(const Bucket& rhs) const;
	bool operator!=(const Bucket& rhs) const;

	bool operator<(const Bucket& rhs) const;
	bool operator<=(const Bucket& rhs) const;
	bool operator>(const Bucket& rhs) const;
	bool operator>=(const Bucket& rhs) const;

	void addEgg(const Egg& egg);
	void removeEgg(const char* name);
	void print() const;

	void setOwner(char* owner);
	const char* getOwner() const;

	Egg* getContainer() const;

	int getSize() const;
	int getElementsCount() const;

private:
	char owner[32];
	int containerSize;
	int elementsCount;
	Egg* container;

	void addTwiceSpace(Egg* container);
	void removeHalfSpace(Egg* container);
};

#endif
