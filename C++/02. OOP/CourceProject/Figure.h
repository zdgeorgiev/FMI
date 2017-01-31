#ifndef FIGURE_HEADER_INCLUDED
#define FIGURE_HEADER_INCLUDED

#include <string>
#include <iostream>
#include "Point.h"

using namespace std;

class Figure
{
public:

	Figure(string name, Point startPoint, string color, string svgTag);
	Figure();
	virtual ~Figure();
	Figure(const Figure& rhs);

	Figure& operator=(const Figure& rhs);

	virtual string toSVGString() const;
	virtual void print() const;

	void translate(int horizontal, int vertical);

	Point getStartingPoint() const;
	string getName() const;
	string getColor() const;
	string getSVGTag() const;

private:
	Point startPoint;
	string name, color, svgTag;

	void setName(string name);
	void setColor(string color);
	void setSVGTag(string svgTag);
};

#endif