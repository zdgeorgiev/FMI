#include <iostream>

using namespace std;

static bool CheckForLeapYear(int year);

static int GetCurrentMonthDays(int month, int year);

static bool CheckForCorrectDate(int day, int month, int year);

static void PrintPreviousDate(int day, int month, int year);

int main()
{
	int day;
	int month;
	int year;

	printf("day = ");
	cin >> day;
	printf("month = ");
	cin >> month;
	printf("year = ");
	cin >> year;

	if (CheckForCorrectDate(day, month, year))
	{
		printf("Current date  : %02d.%02d.%04d\n", day, month, year);
		PrintPreviousDate(day, month, year);
	}
	else
	{
		printf("Invalid date\n");
	}

	return 0;
}

static bool CheckForCorrectDate(int day, int month, int year)
{
	if ((day <= 0 || day > 31) || (month <= 0 || month > 12) || (year <= 0))
	{
		return false;
	}

	bool isDateCorrect = true;
	int currentMonthDays = GetCurrentMonthDays(month, year);

	//If the day is bigger than the last day of the month
	if (day > currentMonthDays)
	{
		isDateCorrect = false;
	}

	return isDateCorrect;
}

static bool CheckForLeapYear(int year)
{
	//Years devided by 4 with remainder 0 are leap, others arent;
	//Exception 1: years, devided by 100 with remainder 0 arent leap;
	//Exception 2: years, devided by 400 with remainder 0 are leap;
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	return false;
}

static int GetCurrentMonthDays(int month, int year)
{
	int currentMonthDays = 0;
	bool isLeap = CheckForLeapYear(year);

	//28 days - 2 (if isnt leap year)
	//29 days - 2 (if is leap year)
	//30 days - 4 6 -- 9 11
	//31 days - 1 3 5 7 -- 8 10 12

	if (month == 2)
	{
		if (isLeap)
		{
			currentMonthDays = 29;
		}
		else
		{
			currentMonthDays = 28;
		}
	}
	else if (month < 8)
	{
		if (month % 2 == 0)
		{
			currentMonthDays = 30;
		}
		else
		{
			currentMonthDays = 31;
		}
	}
	else if (month >= 8)
	{
		if (month % 2 == 0)
		{
			currentMonthDays = 31;
		}
		else
		{
			currentMonthDays = 30;
		}
	}

	return currentMonthDays;
}

static void PrintPreviousDate(int day, int month, int year)
{
	if (day == 1 && month == 1 && year == 1)
	{
		printf("There isnt previous date\n");
	}
	else
	{
		int currentMonthDays = GetCurrentMonthDays(month, year);

		if (day - 1 == 0)
		{
			if (month - 1 == 0)
			{
				month = 12;
				year--;
			}
			else
			{
				month--;
			}

			day = GetCurrentMonthDays(month, year);
		}
		else
		{
			day--;
		}

		printf("Previous date : %02d.%02d.%04d\n", day, month, year);
	}
}