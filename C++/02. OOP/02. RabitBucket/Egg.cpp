#include "Egg.h"
#include <iostream>

Egg::Egg(const char * name, int size)
{
	setName(name);
	setSize(size);
}

Egg::Egg()
{
	setName("");
	setSize(0);
}

Egg::Egg(const Egg & rhs)
{
	strcpy(this->name, rhs.getName());
	this->size = rhs.size;
}

Egg::~Egg()
{
	setName("\0");
	setSize(0);
}

Egg & Egg::operator=(const Egg & rhs)
{
	if (this != &rhs)
	{
		strcpy(this->name, rhs.getName());
		this->size = rhs.size;
	}

	return *this;
}

void Egg::setName(const char * name)
{
	strncpy(this->name, name, sizeof(this->name) - 1);
}

const char * Egg::getName() const
{
	return this->name;
}

void Egg::setSize(const int size)
{
	this->size = size;
}

const int Egg::getSize() const
{
	return this->size;
}

void Egg::print() const
{
	std::cout << "Egg : " << this->name << " " << this->size << std::endl;
}
