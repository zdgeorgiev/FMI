#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int n;
	cin >> n;

	if (n < 2 || n > 128)
	{
		return 0;
	}

	int** matrix = new (nothrow)int*[n];
	if (!matrix)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new (nothrow)int[n];
			if (!matrix[i])
			{
				for (int j = 0; j < i; j++)
				{
					delete[] matrix[j];
				}
				delete[] matrix;
				return 1;
			}
		}
	}

	int currentNumber = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = currentNumber;
			currentNumber++;
		}
	}

	int row = 0;
	int col = 0;
	bool visited[100][100] = { 0 };
	char direction = 'r';
	int requiredNumbers = n * n;

	while (requiredNumbers)
	{
		if (direction == 'r')
		{
			while (col < n && !visited[row][col])
			{
				cout << matrix[row][col] << " ";
				requiredNumbers--;
				visited[row][col] = true;
				col++;
			}

			col--;
			row++;
			direction = 'd';
		}
		else if (direction == 'd')
		{
			while (row < n && !visited[row][col])
			{
				cout << matrix[row][col] << " ";
				requiredNumbers--;
				visited[row][col] = true;
				row++;
			}

			row--;
			col--;
			direction = 'l';
		}
		else if (direction == 'l')
		{
			while (col >= 0 && !visited[row][col])
			{
				cout << matrix[row][col] << " ";
				requiredNumbers--;
				visited[row][col] = true;
				col--;
			}

			col++;
			row--;
			direction = 'u';
		}
		else if (direction == 'u')
		{
			while (row >= 0 && !visited[row][col])
			{
				cout << matrix[row][col] << " ";
				requiredNumbers--;
				visited[row][col] = true;
				row--;
			}

			row++;
			col++;
			direction = 'r';
		}
	}

	cout << endl;

	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;

	return 0;
}