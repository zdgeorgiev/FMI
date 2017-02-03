/**
*
* Solution to course project
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Georgiev
* @idnumber 45115
* @task course project
* @compiler VC
*
*/
#include "ArchiverUtils.h"

enum CommandType
{
	COMPRESS,
	DECOMPRESS,
	LIST,
	INVALID
};

CommandType getCommand(char* argv[])
{
	if (!strcmp(argv[1], "-Pack"))
		return COMPRESS;
	if (!strcmp(argv[1], "-Unpack"))
		return DECOMPRESS;
	if (!strcmp(argv[1], "-List"))
		return LIST;
	return INVALID;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
		return -1;

	char* source = argv[2];
	char* destination = argc < 4 ? "" : argv[3];

	switch (getCommand(argv))
	{
	case COMPRESS:
	{
		ArchiverUtils::compress(source, destination); break;
	}
	case DECOMPRESS:
	{
		ArchiverUtils::decompress(source, destination); break;
	}
	case LIST:
	{
		ArchiverUtils::listAllFiles(source, std::cout); break;
	}
	default:
		throw "Invalid command";
	}

	system("pause");
	return 0;
}