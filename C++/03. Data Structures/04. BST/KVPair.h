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

#ifndef __KVPAIR_HEADER_INCLUDED__
#define __KVPAIR_HEADER_INCLUDED__

#include <iostream>

class KVPair
{
private:
	int key;
	char* value;

public:
	KVPair(int key = 0, char* value = nullptr)
	{
		this->key = key;
		this->value = value;
	}

	int getKey() const
	{
		return this->key;
	}

	char* getValue() const
	{
		return this->value;
	}

	bool operator<(const KVPair& rhs) const
	{
		return this->getKey() < rhs.getKey();
	}

	bool operator>(const KVPair& rhs) const
	{
		return this->getKey() > rhs.getKey();
	}

	bool operator==(const KVPair& rhs) const
	{
		return this->getKey() == rhs.getKey() && !strcmp(this->getValue(), rhs.getValue());
	}
};

#endif