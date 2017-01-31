#include "Rectangle.h"

Rectangle::Rectangle(Point startingPoint, int width, int height, string color) : Figure("rectangle", startingPoint, color, "rect")
{
	setWidth(width);
	setHeight(height);
}

Rectangle::Rectangle() : Figure()
{
	setWidth(0);
	setHeight(0);
}

Rectangle::~Rectangle()
{
	Figure::~Figure();
	setWidth(0);
	setHeight(0);
}

Rectangle::Rectangle(const Rectangle & rhs)
{
	Figure::Figure(rhs);
	setWidth(rhs.width);
	setHeight(rhs.height);
}

Rectangle & Rectangle::operator=(const Rectangle & rhs)
{
	if (this != &rhs)
	{
		Figure::operator=(rhs);
		setWidth(rhs.width);
		setHeight(rhs.height);
	}

	return *this;
}

void Rectangle::print() const
{
	Figure::print();
	cout << " " << this->width << " " << this->height << endl;
}

string Rectangle::toSVGString() const
{
	string svgRepresentation;

	svgRepresentation.append("<");

	svgRepresentation.append(this->getSVGTag()).append(" ");
	svgRepresentation.append("x=\"").append(to_string(this->getStartingPoint().getX())).append("\" ");
	svgRepresentation.append("y=\"").append(to_string(this->getStartingPoint().getY())).append("\" ");
	svgRepresentation.append("width=\"").append(to_string(this->getWidth())).append("\" ");
	svgRepresentation.append("height=\"").append(to_string(this->getHeight())).append("\" ");
	svgRepresentation.append("fill=\"").append(this->getColor()).append("\" ");

	svgRepresentation.append("/>");

	return svgRepresentation;
}

void Rectangle::setWidth(int width)
{
	if (width < 0)
		cout << "With should be a positive number" << endl;
	else
		this->width = width;
}

int Rectangle::getWidth() const
{
	return this->width;
}

void Rectangle::setHeight(int height)
{
	if (height < 0)
		cout << "Height must be a positive number" << endl;
	else
		this->height = height;
}

int Rectangle::getHeight() const
{
	return this->height;
}
