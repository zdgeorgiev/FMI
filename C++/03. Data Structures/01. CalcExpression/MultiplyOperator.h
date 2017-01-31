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

#ifndef __MULTIPLY_OPERATOR_HEADER_INCLUDED__
#define __MULTIPLY_OPERATOR_HEADER_INCLUDED__

#include "Operator.h"

class MultiplyOperator : public Operator {

public:

	MultiplyOperator(char symbol, int priority, int associative) : Operator(symbol, priority, associative) { };

	virtual float apply(float leftOperand, float rightOperand) const;
};

#endif
