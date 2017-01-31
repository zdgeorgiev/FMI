#ifndef FIGURE_CONTAINER_HEADER_INCLUDED
#define FIGURE_CONTAINER_HEADER_INCLUDED

#include <iostream>
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "FigureUtils.h"

using namespace std;

class FigureContainer
{
public:

	FigureContainer();
	~FigureContainer();
	FigureContainer(const FigureContainer& rhs);

	FigureContainer& operator=(const FigureContainer& rhs);
	Figure& operator[](int index) const;

	bool addFigure(string shape, string rawParams);
	void removeAt(int index);

	int getSize() const;

private:

	Figure** figures;

	int containerSize;
	int elementsCount;

	void addTwiceMoreSpace();
	void removeHalfSpace();
};

#endif