#include "Ellipse.h"

Ellipse::Ellipse(Point startingPoint, int xRadius, int yRadius, string color) : Figure("ellipse", startingPoint, color, "ellipse")
{
	this->setXRadius(xRadius);
	this->setYRadius(yRadius);
}

Ellipse::Ellipse()
{
	Figure::Figure();
	this->setXRadius(0);
	this->setYRadius(0);
}

Ellipse::~Ellipse()
{
	this->setXRadius(0);
	this->setYRadius(0);
}

Ellipse::Ellipse(const Ellipse & rhs)
{
	this->setXRadius(rhs.getXRadius());
	this->setYRadius(rhs.getYRadius());
}

Ellipse & Ellipse::operator=(const Ellipse & rhs)
{
	Figure::operator=(rhs);
	this->setXRadius(rhs.getXRadius());
	this->setYRadius(rhs.getYRadius());
	return *this;
}

void Ellipse::print() const
{
	Figure::print();
	cout << " " << this->xRadius << " " << this->yRadius << endl;
}

bool Ellipse::isPointIn(Point point) const
{
	return ((point.getX() - this->getStartingPoint().getX()) * (point.getX() - this->getStartingPoint().getX()) / (this->getXRadius() * this->getXRadius())) +
		   ((point.getY() - this->getStartingPoint().getY()) * (point.getY() - this->getStartingPoint().getY()) / (this->getYRadius() * this->getYRadius())) <= 1;
}

string Ellipse::toSVGString() const
{
	string svgRepresentation;

	svgRepresentation.append("<");

	svgRepresentation.append(this->getSVGTag()).append(" ");
	svgRepresentation.append("cx=\"").append(to_string(this->getStartingPoint().getX())).append("\" ");
	svgRepresentation.append("cy=\"").append(to_string(this->getStartingPoint().getY())).append("\" ");
	svgRepresentation.append("rx=\"").append(to_string(this->getXRadius())).append("\" ");
	svgRepresentation.append("ry=\"").append(to_string(this->getYRadius())).append("\" ");
	svgRepresentation.append("fill=\"").append(this->getColor()).append("\" ");

	svgRepresentation.append("/>");

	return svgRepresentation;
}

int Ellipse::getXRadius() const
{
	return this->xRadius;
}

int Ellipse::getYRadius() const
{
	return this->yRadius;
}

void Ellipse::setXRadius(int xRadius)
{
	if (xRadius < 0)
		cout << "X radius should be a positive number" << endl;
	else
		this->xRadius = xRadius;
}

void Ellipse::setYRadius(int yRadius)
{
	if (yRadius < 0)
		cout << "Y radius should be a positive number" << endl;
	else
		this->yRadius = yRadius;
}
