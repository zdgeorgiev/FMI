#ifndef SVG_FILE_HEADER_INCLUDED
#define SVG_FILE_HEADER_INCLUDED

#include <string>
#include "FigureContainer.h"
#include "Circle.h"
#include "Rectangle.h"
#include "GeometryUtils.h"

using namespace std;

class SVGFile
{
public:

	SVGFile(string content);
	SVGFile();
	~SVGFile();

	void printFigures() const;

	void createFigure(string figure, string params);
	void eraseFigure(int figureIndex);

	void translateFigure(int index, int horizontal, int vertical) const;
	void translateAllFigures(int horizontal, int vertical) const;

	void printAllFiguresWithinCircle(const Circle& circle) const;
	void printAllFiguresWithinRectangle(const Rectangle& rectangle) const;

	string getContent() const;

private:

	static const string SVG_FILE_HEADER;

	FigureContainer* figures;

	void parseContent(string content);

};

#endif