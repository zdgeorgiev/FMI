#include <iostream>

using namespace std;

int main()
{
	int firstNumber;
	int secondNumber;

	cin >> firstNumber >> secondNumber;

	//Make sure to use the correct range from min to max
	int maxNumber = firstNumber > secondNumber ? firstNumber : secondNumber;
	int minNumber = maxNumber == firstNumber ? secondNumber : firstNumber;

	int primeDividersSumCount = 0;

	for (int i = minNumber; i <= maxNumber; i++)
	{
		int currentNumber = i;
		int currentSum = 0;

		//Search for all dividers except the number itself!
		for (int divider = currentNumber; divider > 1; divider--)
		{
			if (currentNumber % divider == 0)
			{
				currentSum += currentNumber / divider;
			}
		}

		bool isSumPrime = true;

		for (int divider = 2; divider <= currentSum / 2; divider++)
		{
			if (currentSum % divider == 0)
			{
				isSumPrime = false;
				break;
			}
		}

		if (isSumPrime && currentSum > 1)
		{
			primeDividersSumCount++;
			printf("%d ", i);
		}
	}

	printf("\nNumbers with prime sum of dividers : %d\n", primeDividersSumCount);

	return 0;
}