#include <iostream>

//Can hold variations up to 2^15
char result[32768][100] = { 0 };
int row = 0;

//Added additional parameter index to recieve the result in
//lexicographical order
void Gen01(int index, int lenght, char* input)
{
	if (index == lenght)
	{
		strcpy(result[row++], input);
		return;
	}

	if (input[index] != '*')
	{
		Gen01(index + 1, lenght, input);
	}
	else
	{
		for (char i = '0'; i < '2'; i++)
		{
			input[index] = i;
			Gen01(index + 1, lenght, input);
		}

		input[index] = '*';
	}
}

void Print()
{
	for (size_t i = 0; i < row; i++)
	{
		printf("%s\n", result[i]);
	}
}

int main()
{
	char input[128];
	std::cin.getline(input, 128);
	int lenght = strlen(input);

	Gen01(0, lenght, input);

	Print();

	return 0;
}