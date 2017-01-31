#ifndef CIRCLE_HEADER_INCLUDED
#define CIRCLE_HEADER_INCLUDED

#include "Figure.h"
#include "Rectangle.h"

#include <iostream>

using namespace std;

class Circle : public Figure
{
public:

	Circle(Point startPoint, int radius, string color);
	Circle();
	~Circle();
	Circle(const Circle& rhs);

	Circle& operator=(const Circle& rhs);

	virtual void print() const;
	virtual string toSVGString() const;

	int getRadius() const;

private:

	int radius;

	void setRadius(int radius);
};

#endif