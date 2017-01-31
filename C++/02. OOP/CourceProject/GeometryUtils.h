#ifndef GEOMETRY_UTILS_HEADER_INCLUDED
#define GEOMETRY_UTILS_HEADER_INCLUDED

#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class GeometryUtils
{

public:
	static double getDistance(Point from, Point to);

	//Is first inside second
	static bool isInsideRectangle(const Point& point, const Rectangle & second);
	static bool isInsideRectangle(const Rectangle& first, const Rectangle& second);
	static bool isInsideRectangle(const Circle& first, const Rectangle& second);
	static bool isInsideRectangle(const Line& first, const Rectangle& second);

	static bool isInsideCircle(const Rectangle& first, const Circle& second);
	static bool isInsideCircle(const Circle& first, const Circle& second);
	static bool isInsideCircle(const Line& first, const Circle& second);
};

#endif
