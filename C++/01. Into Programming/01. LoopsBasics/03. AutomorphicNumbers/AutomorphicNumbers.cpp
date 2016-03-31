#include <iostream>
#include <limits>

using namespace std;

int main()
{
	int firstNumbers;

	printf("First ");
	scanf("%d", &firstNumbers);

	printf("First %d automorphic numbers are\n", firstNumbers);

	int counter = 0;
	unsigned long long maxValue = sqrt(ULLONG_MAX);

	for (unsigned long long i = 1; i <= maxValue; i++)
	{
		unsigned long long currentNumber = i;
		unsigned long long targetNumber = pow(i, 2);
		bool isAutomorphic = true;

		//Get the last digit from each of the numbers until atleast one of the numbers is 0
		while (currentNumber != 0 && targetNumber != 0)
		{
			//if current last digits arent equal, then the number isnt automorphic
			if (currentNumber % 10 != targetNumber % 10)
			{
				isAutomorphic = false;
				break;
			}
			else
			{
				currentNumber /= 10;
				targetNumber /= 10;
			}
		}

		if (isAutomorphic)
		{
			counter++;
			printf("%8d\n", i);
		}

		if (counter == firstNumbers)
		{
			break;
		}
	}

	return 0;
}