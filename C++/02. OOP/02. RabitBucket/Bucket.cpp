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
	}

	return *this;
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

const Egg * Bucket::getContainer() const
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
