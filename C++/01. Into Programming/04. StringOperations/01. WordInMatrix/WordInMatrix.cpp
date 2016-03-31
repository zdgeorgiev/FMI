#include <iostream>

static int rows, cols;
static int nextIndex = 1;

static bool visited[100][100] = { 0 };
static char matrix[100][100] = { 0 };

static bool isFound = false;

static int directions[][2] =
{
	//Down,		 Up,	 Down-Right
	{ 1, 0 }, { -1, 0 }, { 1, 1 },
	//Up-Left,	 Right,		Left
	{ -1, -1 }, { 0, 1 }, { 0, -1 },
	//Up-Right, Down-Left
	{ -1, 1 }, { 1, -1 }
};

bool IsTheCellAvaible(int row, int col)
{
	return (row >= 0 && row < rows && col >= 0 & col < cols) && !visited[row][col];
}

void DFS(int row, int col, char* word, int index)
{
	char targetLetter = word[nextIndex];
	visited[row][col] = true;

	//if reach end of the word
	if (targetLetter == '\0')
	{
		int wordLength = strlen(word);

		if (nextIndex == wordLength)
		{
			isFound = true;
			return;
		}
	}

	nextIndex++;

	for (size_t i = 0; i < 8; i++)
	{
		int newRow = row + directions[i][0];
		int newCol = col + directions[i][1];

		if (IsTheCellAvaible(newRow, newCol) && matrix[newRow][newCol] == targetLetter)
		{
			DFS(newRow, newCol, word, nextIndex);
		}
	}

	//If it goes to the wrong direction and when turn back
	//mark the last cell as unvisited and search for previous letter
	if (!isFound)
	{
		nextIndex--;
		visited[row][col] = false;
	}
}

void CheckIfExist(char word[])
{
	int wordLength = strlen(word);

	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			//Find the index where the word can start
			if (matrix[row][col] == word[0])
			{
				nextIndex = 1;
				isFound = false;

				DFS(row, col, word, 0);

				//Reset the bool matrix
				for (size_t row = 0; row < rows; row++)
				{
					for (size_t col = 0; col < cols; col++)
					{
						visited[row][col] = false;
					}
				}

				if (isFound)
				{
					std::cout << "YES" << std::endl;
					return;
				}
			}
		}
	}

	std::cout << "NO" << std::endl;
}

int main()
{
	std::cin >> rows >> cols;

	int n;
	std::cin >> n;

	// 3 < N <= M < 100
	if (rows <= 3 || rows > cols || cols >= 100)
	{
		return 1;
	}

	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			std::cin >> matrix[row][col];
		}
	}

	std::cin.sync();

	for (int i = 0; i < n; i++)
	{
		char currentWord[1024];
		std::cin.getline(currentWord, 1024);

		CheckIfExist(currentWord);
	}

	return 0;
}