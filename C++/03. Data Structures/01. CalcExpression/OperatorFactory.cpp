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
#include "OperatorFactory.h"
#include "AddOperator.h"
#include "SubtractOperator.h"
#include "DevideOperator.h"
#include "MultiplyOperator.h"

OperatorFactory::OperatorFactory(char * initFile) {

	operators = new char[8];
	operatorsSize = 2;
	operatorIndex = 0;

	ifstream is(initFile);
	init(is);

	is.clear();
	is.close();
}

OperatorFactory::~OperatorFactory()
{
	delete operators;
}

void OperatorFactory::init(ifstream & is) {

	char buffer[128];

	while (true) {
		is.getline(buffer, 128);

		if (strlen(buffer) == 0)
			break;

		operators[operatorIndex] = buffer[0];
		operators[operatorIndex + 1] = buffer[2];
		operators[operatorIndex + 2] = buffer[4];
		operatorIndex += 3;

		if (operatorIndex / 3 == operatorsSize) {
			char* newOperators = new char[operatorsSize * 2 * 3];

			for (size_t i = 0; i < operatorIndex; i++) {
				newOperators[i] = operators[i];
			}

			operatorsSize *= 2;
			operators = newOperators;
		}
	}
}

Operator * OperatorFactory::get(char operatorIndentifier) {

	char* operatorProps = getOperator(operatorIndentifier);
	char mathOperator = operatorProps[0];
	char associativity = operatorProps[1];

	switch (mathOperator)
	{
	case '+': return new AddOperator(operatorIndentifier, 1, associativity); break;
	case '-': return new SubtractOperator(operatorIndentifier, 1, associativity); break;
	case '/': return new DevideOperator(operatorIndentifier, 2, associativity); break;
	case '*': return new MultiplyOperator(operatorIndentifier, 3, associativity); break;
	default:
		throw "Operation is not defined";
	}
}

char* OperatorFactory::getOperator(char operatorIndentifier) {

	char* operatorsProps = new char[9];

	for (int i = 0; i < strlen(operators); i += 3) {

		if (operators[i] == operatorIndentifier) {
			operatorsProps[0] = operators[i + 1];
			operatorsProps[1] = operators[i + 2];
			operatorsProps[2] = '\0';
			break;
		}
	}

	return operatorsProps;
}