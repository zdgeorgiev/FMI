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

	void addEgg(const Egg& egg);
	void removeEgg(const char* name);
	void print() const;

	void setOwner(char* owner);
	const char* getOwner() const;

	const Egg* getContainer() const;

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
