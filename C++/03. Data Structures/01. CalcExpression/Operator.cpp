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
#include "Operator.h"

Operator::Operator(char symbol, int priority, int associative) : symbol(symbol), priority(priority), associative(associative)
{
}
