#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int firstRowNumber = (n + 1) / 2;
	int numbersAtRow = 2 - (n % 2);
	int leadingSpaces = n - 1;
	int currentNumber = firstRowNumber;

	//Print the upper triangle
	for (int i = 0; i < (n + 1) / 2; i++)
	{
		currentNumber = firstRowNumber;

		for (int k = 0; k < leadingSpaces; k++)
		{
			printf(" ");
		}

		for (int j = 0; j < numbersAtRow; j++)
		{
			printf("%d ", currentNumber);
			currentNumber++;
		}

		firstRowNumber--;
		leadingSpaces -= 2;
		numbersAtRow += 2;

		printf("\n");
	}

	if (n % 2 == 0)
	{
		for (int i = 1; i <= n; i++)
		{
			printf(" %d", i);
		}

		printf("\n");
	}

	firstRowNumber += 2;
	numbersAtRow = n - 2;
	leadingSpaces = 3 - (n % 2);

	//Print the lower triangle
	for (int i = (n + 1) / 2 - 1; i > 0; i--)
	{
		currentNumber = firstRowNumber;

		for (int k = 0; k < leadingSpaces; k++)
		{
			printf(" ");
		}

		for (int j = 0; j < numbersAtRow; j++)
		{
			printf("%d ", currentNumber);
			currentNumber++;
		}

		firstRowNumber++;
		leadingSpaces += 2;
		numbersAtRow -= 2;

		printf("\n");
	}

	return 0;
}