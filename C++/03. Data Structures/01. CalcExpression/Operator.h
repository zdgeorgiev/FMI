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

#ifndef __OPERATOR_HEADER_INCLUDED__
#define __OPERATOR_HEADER_INCLUDED__

class Operator {

protected:
	int priority;
	int associative;
	char symbol;
	
public:

	Operator(char symbol, int priority, int associative);

	virtual float apply(float leftOperand, float rightOperand) const = 0;

	char getSymbol() const { return symbol; }
};

#endif
