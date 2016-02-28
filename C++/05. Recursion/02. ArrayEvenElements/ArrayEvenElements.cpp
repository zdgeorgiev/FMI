#include <iostream>

void Process(int index, const int* from, int* to)
{
	if (index < 0)
	{
		return;
	}

	if (*from % 2 == 0)
	{
		*to = *from;
		to++;
	}

	from++;

	return Process(index - 1, from, to);
}

int main()
{
	int n;
	std::cin >> n;

	int arr[1000] = { 0 };
	int resultArr[1000] = { 0 };

	for (size_t i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}

	Process(n, arr, resultArr);

	std::cout << std::endl;

	for (size_t i = 0; i < n; i++)
	{
		int currentNumber = resultArr[i];

		if (currentNumber == 0)
		{
			break;
		}

		std::cout << currentNumber << std::endl;
	}

	return 0;
}