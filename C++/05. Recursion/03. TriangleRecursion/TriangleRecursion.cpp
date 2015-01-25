#include <iostream>

void Print(int n, int start, int count)
{
	if (n == 0)
	{
		return;
	}

	if (count > n)
	{
		Print(n - 1, 1, n - 1);
	}
	else
	{
		if (start > count)
		{
			std::cout << std::endl;
			Print(n, 1, count + 1);
		}
		else
		{
			std::cout << start << " ";
			Print(n, start + 1, count);
		}
	}
}

int main()
{
	int n;
	std::cin >> n;

	Print(n, 1, 1);

	return 0;
}