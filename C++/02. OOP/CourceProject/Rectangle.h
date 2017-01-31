#ifndef RECTANGLE_HEADER_INCLUDED
#define RECTANGLE_HEADER_INCLUDED

#include "Figure.h"

#include <iostream>

using namespace std;

class Rectangle : virtual public Figure
{
public:

	Rectangle(Point startingPoint, int width, int height, string color);
	Rectangle();
	~Rectangle();
	Rectangle(const Rectangle& rhs);

	Rectangle& operator=(const Rectangle& rhs);

	virtual void print() const;
	virtual string toSVGString() const;

	int getWidth() const;
	int getHeight() const;

	void setWidth(int width);
	void setHeight(int height);

private:

	int width, height;
};

#endif
