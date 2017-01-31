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

#ifndef __OPERATOR_FACTORY_HEADER_INCLUDED__
#define __OPERATOR_FACTORY_HEADER_INCLUDED__

#include "Operator.h"

#include <iostream>
#include <fstream>

using namespace std;

class OperatorFactory {

private:
	char * operators;
	int operatorsSize;
	int operatorIndex;

	void init(ifstream & is);

	char* getOperator(char operatorIndentifier);

public:

	OperatorFactory(char* initFile);
	~OperatorFactory();

	Operator* get(char op);
};

#endif