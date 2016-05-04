#include "Bucket.h"
#include <iostream>

Bucket::Bucket(char * owner)
{
	this->setOwner(owner);
	this->elementsCount = 0;
	this->containerSize = 1;
	this->container = new Egg[containerSize];
}

Bucket::Bucket()
{
	this->setOwner("");
	this->elementsCount = 0;
	this->containerSize = 1;
	this->container = new Egg[containerSize];
}

Bucket::~Bucket()
{
	delete[] this->container;
}

Bucket::Bucket(const Bucket & rhs)
{
	strcpy(this->owner, rhs.getOwner());
	this->containerSize = rhs.containerSize;
	this->elementsCount = rhs.elementsCount;

	this->container = new Egg[rhs.containerSize];
	memcpy(this->container, rhs.container, rhs.elementsCount * sizeof(Egg));
}

Bucket & Bucket::operator=(const Bucket & rhs)
{
	if (this != &rhs)
	{
		strcpy(this->owner, rhs.getOwner());
		this->containerSize = rhs.containerSize;

		this->container = new Egg[rhs.containerSize];
		memcpy(this->container, rhs.container, rhs.elementsCount * sizeof(Egg));

		this->elementsCount = rhs.getElementsCount();
		this->containerSize = rhs.getSize();
	}

	return *this;
}

Egg & Bucket::operator[](int index) const
{
	return this->container[index];
}

Egg & Bucket::operator[](char name[64]) const
{
	for (size_t i = 0; i < this->elementsCount; i++)
	{
		if (strcmp(this->container[i].getName(), name) == 0)
			return this->container[i];
	}
}

Bucket Bucket::operator%(const Bucket & rhs) const
{
	Bucket newBucket;

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		for (size_t j = 0; j < rhs.getElementsCount(); j++)
		{
			if (this->container[i] == rhs.getContainer()[j])
				newBucket.addEgg(this->container[i]);
		}
	}

	return newBucket;
}

Bucket & Bucket::operator%=(const Bucket & rhs)
{
	Bucket newBucket = Bucket();

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		for (size_t j = 0; j < rhs.getElementsCount(); j++)
		{
			if (this->container[i] == rhs.getContainer()[j])
				newBucket.addEgg(this->container[i]);
		}
	}

	*this = newBucket;
	return *this;
}

Bucket Bucket::operator+(const Bucket & rhs) const
{
	Bucket newBucket = *this;

	for (size_t i = 0; i < rhs.getElementsCount(); i++)
	{
		newBucket.addEgg(rhs.getContainer()[i]);
	}

	return newBucket;
}

Bucket & Bucket::operator+=(const Bucket & rhs)
{
	Bucket newBucket = *this;

	for (size_t i = 0; i < rhs.getElementsCount(); i++)
	{
		newBucket.addEgg(rhs.getContainer()[i]);
	}

	*this = newBucket;
	return *this;
}

Bucket Bucket::operator*(int size)
{
	Bucket newBucket = Bucket(this->owner);

	for (int i = 0; i < this->elementsCount; i++)
		newBucket.addEgg(Egg(this->container[i].getName, this->container[i].getSize * size));

	return newBucket;
}

Bucket & Bucket::operator*=(int size) const
{
	for (int i = 0; i < this->elementsCount; i++)
		this->container[i].setSize(this->getContainer()[i].getSize() * size);
}

Bucket Bucket::operator/(int size)
{
	Bucket newBucket = Bucket(this->owner);

	for (int i = 0; i < this->elementsCount; i++)
		newBucket.addEgg(Egg(this->container[i].getName, this->container[i].getSize / size));

	return newBucket;
}

Bucket & Bucket::operator/=(int size) const
{
	for (int i = 0; i < this->elementsCount; i++)
		this->container[i].setSize(this->getContainer()[i].getSize() / size);
}

bool Bucket::operator==(const Bucket & rhs) const
{
	if (this->elementsCount != rhs.getSize())
		return false;

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		if (this->getContainer()[i] != rhs.getContainer()[i])
			return false;
	}

	return true;
}

bool Bucket::operator!=(const Bucket & rhs) const
{
	return !(*this == rhs);
}

bool Bucket::operator<(const Bucket & rhs) const
{
	for (size_t i = 0; i < this->getElementsCount(); i++)
	{
		if (this->getContainer()[i] < rhs.getContainer()[i])
			return true;
	}

	return false;
}

bool Bucket::operator<=(const Bucket & rhs) const
{
	for (size_t i = 0; i < this->getElementsCount(); i++)
	{
		if (this->getContainer()[i] <= rhs.getContainer()[i])
			return true;
	}

	return false;
}

bool Bucket::operator>(const Bucket & rhs) const
{
	for (size_t i = 0; i < this->getElementsCount(); i++)
	{
		if (this->getContainer()[i] > rhs.getContainer()[i])
			return true;
	}

	return false;
}

bool Bucket::operator>=(const Bucket & rhs) const
{
	for (size_t i = 0; i < this->getElementsCount(); i++)
	{
		if (this->getContainer()[i] >= rhs.getContainer()[i])
			return true;
	}

	return false;
}

void Bucket::addEgg(const Egg & egg)
{
	if (this->elementsCount == this->containerSize)
		addTwiceSpace(this->container);

	this->container[this->elementsCount] = egg;
	this->elementsCount++;
}

void Bucket::removeEgg(const char * name)
{
	for (size_t i = 0; i < this->elementsCount; i++)
	{
		if (strcmp(this->container[i].getName(), name) == 0)
		{
			//Shift left all remaining elements
			for (size_t j = i + 1; j < this->elementsCount; j++)
			{
				this->container[j - 1] = this->container[j];
			}

			this->elementsCount--;

			if (this->elementsCount * 2 < this->containerSize)
				removeHalfSpace(this->container);

			return;
		}
	}
}

void Bucket::print() const
{
	for (size_t i = 0; i < this->elementsCount; i++)
		this->container[i].print();
}

void Bucket::setOwner(char * owner)
{
	strcpy(this->owner, owner);
}

const char* Bucket::getOwner() const
{
	return this->owner;
}

Egg * Bucket::getContainer() const
{
	return this->container;
}

int Bucket::getSize() const
{
	return this->containerSize;
}

int Bucket::getElementsCount() const
{
	return this->elementsCount;
}

void Bucket::removeHalfSpace(Egg * container)
{
	Egg* newContainer = new Egg[this->containerSize / 2];
	memcpy(newContainer, this->container, this->containerSize / 2 * sizeof(Egg));

	delete[] this->container;
	this->container = newContainer;
	this->containerSize /= 2;
}

void Bucket::addTwiceSpace(Egg * container)
{
	Egg* newContainer = new Egg[this->containerSize * 2];
	memcpy(newContainer, this->container, this->containerSize * sizeof(Egg));

	delete[] this->container;
	this->container = newContainer;
	this->containerSize *= 2;
}

char * operator+(const Bucket & v1, const Bucket & v2)
{
	char concatenated[1024];
	for (size_t i = 0; i < v1.getElementsCount(); i++)
	{
		strcat(concatenated, v1.getContainer()[i].getName());
	}

	for (size_t i = 0; i < v2.getElementsCount(); i++)
	{
		strcat(concatenated, v2.getContainer()[i].getName());
	}

	return concatenated;
}

Bucket & operator+=(Bucket & v1, const Bucket & v2)
{
	char concatenated[1024];
	for (size_t i = 0; i < v1.getElementsCount(); i++)
	{
		strcat(concatenated, v1.getContainer()[i].getName());
	}

	for (size_t i = 0; i < v2.getElementsCount(); i++)
	{
		strcat(concatenated, v2.getContainer()[i].getName());
	}

	v1.setOwner(concatenated);
	return v1;
}
