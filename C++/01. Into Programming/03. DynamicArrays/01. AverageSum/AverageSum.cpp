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

	int* numbers = new (nothrow)int[n];

	if (!numbers)
	{
		return 1;
	}

	int currentIndex = 0;

	float averageSum = 0;

	for (int i = 0; i < n; i++)
	{
		int currentNumber;;
		cin >> currentNumber;

		numbers[i] = currentNumber;

		averageSum += currentNumber;
	}

	averageSum /= n;

	cout << "Average sum - " << averageSum << endl;
	cout << "Numbers bigger than " << averageSum << " - ";

	for (int i = 0; i < n; i++)
	{
		if (numbers[i] > averageSum)
		{
			cout << numbers[i] << " ";
		}
	}

	cout << endl;

	delete[] numbers;

	return 0;
}