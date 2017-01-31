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
#include "DevideOperator.h"

float DevideOperator::apply(float leftOperand, float rightOperand) const {
	if (rightOperand == 0)
		throw "Canno devide with zero";

	return leftOperand / rightOperand;
}
