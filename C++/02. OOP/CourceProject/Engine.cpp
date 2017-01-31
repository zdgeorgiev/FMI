#include "Engine.h"

Engine::Engine()
{
	this->file = new SVGFile();
	this->fm = new FileManager();
}

Engine::~Engine()
{
	delete this->fm;
	delete this->file;
}

void Engine::run()
{
	char commandLine[1024];
	cin.getline(commandLine, 1024);

	while (strlen(commandLine) > 0 && strcmp(commandLine, "exit"))
	{
		char* command = strtok(commandLine, " ");

		if (!strcmp(command, "open"))
			openFile();
		else if (!strcmp(command, "close"))
			closeFile();
		else if (!strcmp(command, "save"))
			saveFile();
		else if (!strcmp(command, "saveas"))
			saveAsFile();
		else if (!strcmp(command, "create"))
			createFigure();
		else if (!strcmp(command, "print"))
			printFigures();
		else if (!strcmp(command, "erase"))
			eraseFigure();
		else if (!strcmp(command, "translate"))
			translate();
		else if (!strcmp(command, "within"))
			printFiguresWithin();
		else
			cout << "Invalid command [" << command << "]" << endl;

		cin.getline(commandLine, 1024);
	}

	cout << "Exit" << endl;
};

void Engine::openFile()
{
	char* filePath = strtok(NULL, " ");

	if ((*this->fm).open(filePath))
	{
		this->file = new SVGFile((*this->fm).getFileContent());
	}
}

void Engine::closeFile()
{
	(*this->fm).close();
}

void Engine::saveFile()
{
	(*this->fm).write((*this->file).getContent(), (*this->fm).getFilePath());
}

void Engine::saveAsFile()
{
	char* filePath = strtok(NULL, " ");
	(*this->fm).write((*this->file).getContent(), filePath);
}

void Engine::createFigure()
{
	if ((*this->fm).getIfFileOpened())
	{
		char * command = strtok(NULL, " ");
		string figure = command;

		string params;

		command = strtok(NULL, " ");
		int paramIndex = 0;
		while (command)
		{
			params.append("\"").append(command).append("\"");
			command = strtok(NULL, " ");
			paramIndex++;
		}

		(*this->file).createFigure(figure, params.substr(0, params.length() - 1));

		params.clear();
		figure.clear();
	}
	else
		cout << "Before creating figure you must open the file" << endl;
}

void Engine::printFigures()
{
	if ((*this->fm).getIfFileOpened())
		(*this->file).printFigures();
	else
		cout << "Before print figures you must open the file" << endl;
}

void Engine::eraseFigure()
{
	char* index = strtok(NULL, " ");

	if ((*this->fm).getIfFileOpened())
		(*this->file).eraseFigure(atoi(index));
	else
		cout << "Before erasing figure you must open the file" << endl;
}

void Engine::translate()
{
	if ((*this->fm).getIfFileOpened())
	{
		char* firstParam = strtok(NULL, " ");
		char* secondParam = strtok(NULL, " ");
		char* thirdParam = strtok(NULL, " ");

		if (thirdParam == NULL)
		{
			if (strlen(firstParam) <= 9 || strlen(secondParam) <= 11)
			{
				cout << "usage - translate [index] vertical:X horizontal:Y" << endl;
				return;
			}

			string verticalNumber = firstParam;
			verticalNumber = verticalNumber.substr(9);
			string horizontalNumber = secondParam;
			horizontalNumber = horizontalNumber.substr(11);

			(*this->file).translateAllFigures(atoi(horizontalNumber.c_str()), atoi(verticalNumber.c_str()));

			verticalNumber.clear();
			horizontalNumber.clear();
		}
		else
		{
			if (strlen(secondParam) <= 9 || strlen(thirdParam) <= 11)
			{
				cout << "usage - translate [index] vertical:X horizontal:Y" << endl;
				return;
			}

			string verticalNumber = secondParam;
			verticalNumber = verticalNumber.substr(9);
			string horizontalNumber = thirdParam;
			horizontalNumber = horizontalNumber.substr(11);

			(*this->file).translateFigure(atoi(firstParam), atoi(horizontalNumber.c_str()), atoi(verticalNumber.c_str()));

			verticalNumber.clear();
			horizontalNumber.clear();
		}
	}
	else
		cout << "Before translating figure you must open the file" << endl;
}

void Engine::printFiguresWithin() const
{
	char* figure = strtok(NULL, " ");

	char* firstParam = strtok(NULL, " ");
	char* secondParam = strtok(NULL, " ");
	char* thirdParam = strtok(NULL, " ");
	char* fourthParam = strtok(NULL, " ");

	if (!strcmp(figure, "rectangle"))
	{
		(*this->file).printAllFiguresWithinRectangle(
			Rectangle(Point(atoi(firstParam), atoi(secondParam)), atoi(thirdParam), atoi(fourthParam), "."));
	}
	else if (!strcmp(figure, "circle"))
	{
		(*this->file).printAllFiguresWithinCircle(
			Circle(Point(atoi(firstParam), atoi(secondParam)), atoi(thirdParam), "."));
	}
	else
		cout << "Invalid figure " << figure << endl;
}
