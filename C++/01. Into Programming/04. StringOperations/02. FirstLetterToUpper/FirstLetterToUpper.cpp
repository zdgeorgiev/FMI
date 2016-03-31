#include <iostream>
#include <iomanip>

static const int KEYWORDS_COUNT = 84;

#pragma region KeyWords C++
static char* keywords[] =
{
	"alignas",
	"alignof",
	"and",
	"and_eq",
	"asm",
	"auto",
	"bitand",
	"bitor",
	"bool",
	"break",
	"case",
	"catch",
	"char",
	"char16_t",
	"char32_t",
	"class",
	"compl",
	"const",
	"constexpr",
	"const_cast",
	"continue",
	"decltype",
	"default",
	"delete",
	"do",
	"double",
	"dynamic_cast",
	"else",
	"enum",
	"explicit",
	"export",
	"extern",
	"false",
	"float",
	"for",
	"friend",
	"goto",
	"if",
	"inline",
	"int",
	"long",
	"mutable",
	"namespace",
	"new",
	"noexcept",
	"not",
	"not_eq",
	"nullptr",
	"operator",
	"or",
	"or_eq",
	"private",
	"protected",
	"public",
	"register",
	"reinterpret_cast",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"static_assert",
	"static_cast",
	"struct",
	"switch",
	"template",
	"this",
	"thread_local",
	"throw",
	"true",
	"try",
	"typedef",
	"typeid",
	"typename",
	"union",
	"unsigned",
	"using",
	"virtual",
	"void",
	"volatile",
	"wchar_t",
	"while",
	"xor",
	"xor_eq",
};
#pragma endregion

bool isKeyword(char word[], char* keywords[])
{
	int inputWordLength = strlen(word);

	for (size_t i = 0; i < KEYWORDS_COUNT; i++)
	{
		bool isKeyWord = true;
		int currentWordLength = strlen(keywords[i]);

		if (currentWordLength != inputWordLength)
		{
			continue;
		}

		for (int j = 0; j < currentWordLength; j++)
		{
			if (word[j] != keywords[i][j])
			{
				isKeyWord = false;
				break;
			}
		}

		if (isKeyWord)
		{
			return true;
		}
	}

	return false;
}

bool IsValidIndent(char input[])
{
	if (isKeyword(input, keywords))
	{
		return false;
	}

	//if the first letter isnt underscore line or letter
	if (input[0] != '_' &&
		((input[0] < 'A' || input[0] > 'Z') && (input[0] < 'a' || input[0] > 'z')))
	{
		return false;
	}

	int inputLength = strlen(input);

	for (size_t i = 1; i < inputLength; i++)
	{
		//Check if the currentLetter ist letter and digit
		if (((input[i] < 'A' || input[i] > 'Z') && (input[i] < 'a' || input[i] > 'z')) && (input[i] < '1' || input[i] > '9'))
		{
			return false;
		}
	}

	return true;
}

int main()
{
	int wordsCount = 4;

	char words[][256] =
	{
		{ "inputValue" },
		{ "_ha" },
		{ "void" },
		{ "%asdasd" },
	};

	for (size_t i = 0; i < wordsCount; i++)
	{
		std::cout << std::setw(10) << words[i] << " -> ";

		if (IsValidIndent(words[i]))
		{
			if (words[i][0] >= 'a' && words[i][0] <= 'z')
			{
				words[i][0] = words[i][0] - 'a' + 'A';
			}

			std::cout << words[i] << std::endl;
		}
		else
		{
			std::cout << "Not valid" << std::endl;
		}
	}

	return 0;
}