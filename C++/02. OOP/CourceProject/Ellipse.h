#ifndef ELLIPSE_HEADER_INCLUDED
#define ELLIPSE_HEADER_INCLUDED

#include "Figure.h"
#include <iostream>

using namespace std;

class Ellipse : public Figure
{
public:

	Ellipse(Point startingPoint, int xRadius, int yRadius, string color);
	Ellipse();
	~Ellipse();
	Ellipse(const Ellipse& rhs);

	Ellipse& operator=(const Ellipse& rhs);

	virtual void print() const;
	virtual bool isPointIn(Point point) const;
	virtual string toSVGString() const;

	int getXRadius() const;
	int getYRadius() const;

private:

	int xRadius;
	int yRadius;

	void setXRadius(int xRadius);
	void setYRadius(int yRadius);
};

#endif