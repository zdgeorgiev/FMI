#ifndef ENGINE_HEADER_INCLUDED
#define ENGINE_HEADER_INCLUDED

#include <iostream>
#include "FileManager.h"
#include "SVGFile.h"

using namespace std;

class Engine
{
public:

	Engine();
	~Engine();

	void run();

private:

	SVGFile* file;
	FileManager* fm;

	void openFile();
	void closeFile();
	void saveFile();
	void saveAsFile();
	void createFigure();
	void printFigures();
	void eraseFigure();
	void translate();
	void printFiguresWithin() const;
};

#endif