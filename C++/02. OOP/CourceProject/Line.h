#ifndef LINE_HEADER_INCLUDED
#define LINE_HEADER_INCLUDED

#include "Figure.h"
#include "Point.h"

#include <iostream>

class Line : public Figure
{
public:

	Line(Point startPoint, Point endPoint, string color);
	Line();
	~Line();
	Line(const Line& rhs);

	Line& operator=(const Line& rhs);

	virtual void print() const;
	virtual string toSVGString() const;

	Point getEndPoint() const;

private:

	Point endPoint;

	void setEndPoint(Point endPoint);
};

#endif