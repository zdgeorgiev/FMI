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
#include "Stack.h"
#include "Operator.h"
#include "OperatorFactory.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

enum Token {
	OPERATOR,
	NUMBER,
	UNKNOWN
};

static bool isNumber(char* token) {

	bool negative = false;
	bool numbersOccur = false;
	bool hasFloatingPoint = false;

	for (size_t i = 0; i < strlen(token); i++)
	{
		if (token[i] - '0' >= 0 && token[i] - '0' < 9) {
			numbersOccur = true;
		}
		else if (token[i] == '-') {
			if (numbersOccur || negative)
				throw "Invalid number";

			negative = true;
		}
		else if (token[i] == '.' || token[i] == ',') {
			
			if (hasFloatingPoint)
				return false;

			hasFloatingPoint = true;
		}
		else {
			return false;
		}
	}

	return numbersOccur;
}

static void printWithPrecision5(double number) {

	int fullPart = 0;

	if ((int)number == 0) {
		fullPart = 0;
	}
	else {

		for (size_t i = 7; i >= 0; i--)
		{
			if (i == 0) {
				fullPart = 1;
				break;
			}

			if ((int)number % (int)pow(10, i) == 0) {
				fullPart = i + 1;
				break;
			}
		}
	}

	cout << setprecision(fullPart + 5) << number << endl;
}

static void printInPostfix(char* expression) {

	Stack<char*> operators;
	Token lastReaded = Token::UNKNOWN;
	char* token = strtok(expression, " ");

	while (token != NULL)
	{
		if (isNumber(token))
		{
			cout << token << " ";

			if (lastReaded == Token::NUMBER) {
				cout << operators.peek() << " ";
				operators.pop();
			}

			lastReaded = Token::NUMBER;
		}
		else
		{
			operators.push(token);
			lastReaded = Token::OPERATOR;
		}

		token = strtok(NULL, " ");
	}

	while (!operators.isEmpty()) {
		cout << operators.peek() << " ";
		operators.pop();
	}

	cout << endl;
}

int main(int argc, char* argv[]) {

	char expression[1024];
	ifstream f(argv[1]);
	f.getline(expression, 1024);

	if (strlen(expression) == 0 || argc != 3) {
		cout << "Error" << endl;
		return 1;
	}

	char* cpyExpression = new char[strlen(expression) + 1];
	strcpy(cpyExpression, expression);

	OperatorFactory factory(argv[2]);

	Stack<double> numbers;
	Stack<Operator*> operators;

	Token lastReaded = Token::UNKNOWN;
	char* token = strtok(expression, " ");

	try {
		// process the input expression till its end
		while (token != NULL)
		{
			if (isNumber(token)) {

				double rightOperand = atof((const char*)token);

				if (lastReaded == Token::NUMBER) {

					if (operators.isEmpty()) {
						cout << "Error" << endl;
						return 1;
					}

					double leftOperand = numbers.peek();
					numbers.pop();

					double afterOperation = operators.peek()->apply(leftOperand, rightOperand);
					operators.pop();

					numbers.push(afterOperation);
				}
				else {
					numbers.push(atof((const char*)token));
					lastReaded = Token::NUMBER;
				}
			}
			else {
				if (strlen(token) != 1) {
					cout << "Error" << endl;
					return 1;
				}

				operators.push(factory.get(token[0]));
				lastReaded = Token::OPERATOR;
			}

			token = strtok(NULL, " ");
		}

		// process the remaining operators and operand from the stacks
		while (!operators.isEmpty()) {

			if (numbers.isEmpty()) {
				cout << "Error" << endl;
				return 1;
			}

			double rightOperand = numbers.peek();
			numbers.pop();

			if (numbers.isEmpty()) {
				cout << "Error" << endl;
				return 1;
			}

			double leftOperand = numbers.peek();
			numbers.pop();

			double afterOperation = operators.peek()->apply(leftOperand, rightOperand);
			operators.pop();

			numbers.push(afterOperation);
		}

		double result = numbers.peek();
		numbers.pop();

		if (!numbers.isEmpty()) {
			cout << "Error" << endl;
			return 1;
		}

		printInPostfix(cpyExpression);
		printWithPrecision5(result);
	}
	catch (const char* msg) {
		cout << "Error" << endl;
	}

	return 0;
}