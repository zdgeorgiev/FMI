#include <iostream>

using namespace std;

int main()
{
	int layer;
	cin >> layer;

	int** pascalPyramid = new int*[layer];

	for (int i = 0; i < layer; i++)
	{
		pascalPyramid[i] = new int[layer + 1];
	}

	int rows = layer;
	int cols = layer + 1;

	//Make all elements 0
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pascalPyramid[i][j] = 0;
		}
	}

	//Default element
	pascalPyramid[0][1] = 1;

	//Numbers to fill in the currentRow
	int numbersToFill = 2;

	//Make pascal triangle
	for (int row = 1; row < rows; row++)
	{
		for (int col = 1; col <= numbersToFill; col++)
		{
			pascalPyramid[row][col] =
				pascalPyramid[row - 1][col - 1] + pascalPyramid[row - 1][col];
		}

		numbersToFill++;
	}

	int leadingSpaces = layer * 2;

	//Convert to pascal pyramid and print each element if its not 0(default)
	for (int row = 0; row < rows; row++)
	{
		int currentMultiplier = pascalPyramid[rows - 1][row + 1];

		//Fill the leading spaces before first number at the current row
		for (int i = 0; i < leadingSpaces; i++)
		{
			printf(" ");
		}

		leadingSpaces -= 2;

		for (int col = 1; col < cols; col++)
		{
			unsigned long long currentNumber = pascalPyramid[row][col];

			currentNumber = currentNumber * currentMultiplier;
			
			if (currentNumber != 0)
			{
				if (col > 1)
				{
					printf("%5d ", currentNumber);
				}
				else
				{
					printf("%d ", currentNumber);
				}
			}
		}

		printf("\n");
	}

	return 0;
}