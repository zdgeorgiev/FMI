#ifndef FIGURE_UTILS_HEADER_INCLUDED
#define FIGURE_UTILS_HEADER_INCLUDED

#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include <string>

class FigureUtils
{

public:

	static Circle* parseCircle(string figureSVGString);
	static Rectangle* parseRectangle(string figureSVGString);
	static Line* parseLine(string figureSVGString);

private:

	static string convertSVGStringToStringArray(string figureSVGString);

};

#endif