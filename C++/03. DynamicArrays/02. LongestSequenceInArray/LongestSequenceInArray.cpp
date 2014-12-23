#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	if (n < 2 || n > 1024)
	{
		return 0;
	}

	int* arr = new (nothrow)int[n];

	if (!arr)
	{
		return 1;
	}

	for (int i = 0; i < n; i++)
	{
		int currentNumber;
		cin >> currentNumber;

		arr[i] = currentNumber;
	}

	int bestLenght = 1;
	int index = -1;

	for (int i = 0; i < n - 1; i++)
	{
		int currentLenght = 1;

		while (arr[i] == arr[i + 1])
		{
			//Dont check outside of the array
			if (i + 1 > n - 1)
			{
				break;
			}

			currentLenght++;
			i++;
		}

		if (currentLenght > bestLenght)
		{
			bestLenght = currentLenght;
			index = i + 1 - currentLenght;
		}
	}

	if (bestLenght != 1)
	{
		cout << "Start from index " << index << endl;
		cout << "Lenght - " << bestLenght << endl;
	}
	else
	{
		cout << "Sequence of numbers not found" << endl;
	}

	delete[] arr;

	return 0;
}