#include "Circle.h"

Circle::Circle(Point startPoint, int radius, string color) : Figure("circle", startPoint, color, "circle")
{
	this->radius = radius;
}

Circle::Circle() : Figure()
{
	this->radius = 0;
}

Circle::~Circle()
{
	Figure::~Figure();
	this->radius = 0;
}

Circle::Circle(const Circle & rhs)
{
	Figure::Figure(rhs);
	this->radius = rhs.radius;
}

Circle & Circle::operator=(const Circle & rhs)
{
	if (this != &rhs)
	{
		Figure::operator=(rhs);
		this->radius = rhs.radius;
	}

	return *this;
}

void Circle::print() const
{
	Figure::print();
	cout << " " << this->radius << endl;
}

string Circle::toSVGString() const
{
	string svgRepresentation;

	svgRepresentation.append("<");

	svgRepresentation.append(this->getSVGTag()).append(" ");
	svgRepresentation.append("cx=\"").append(to_string(this->getStartingPoint().getX())).append("\" ");
	svgRepresentation.append("cy=\"").append(to_string(this->getStartingPoint().getY())).append("\" ");
	svgRepresentation.append("r=\"").append(to_string(this->getRadius())).append("\" ");
	svgRepresentation.append("fill=\"").append(this->getColor()).append("\" ");

	svgRepresentation.append("/>");

	return svgRepresentation;
}

int Circle::getRadius() const
{
	return this->radius;
}

void Circle::setRadius(int radius)
{
	if (radius < 0)
		cout << "Radius must be a positive number" << endl;
	else
		this->radius = radius;
}
