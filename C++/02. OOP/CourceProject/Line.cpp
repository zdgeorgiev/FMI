#include "Line.h"

Line::Line(Point startPoint, Point endPoint, string color) : Figure("line", startPoint, color, "line")
{
	this->setEndPoint(endPoint);
}

Line::Line() : Figure()
{
}

Line::~Line()
{
	Figure::~Figure();
}

Line::Line(const Line & rhs)
{
	Figure::operator=(rhs);
	this->endPoint = rhs.getEndPoint();
}

Line & Line::operator=(const Line & rhs)
{
	if (this != &rhs)
	{
		Figure::operator=(rhs);
		this->endPoint = rhs.getEndPoint();
	}

	return *this;
}

void Line::print() const
{
	Figure::print();
	cout << " " << this->getEndPoint().getX() << " " << this->getEndPoint().getY() << endl;
}

string Line::toSVGString() const
{
	string svgRepresentation;

	svgRepresentation.append("<");

	svgRepresentation.append(this->getSVGTag()).append(" ");
	svgRepresentation.append("x1=\"").append(to_string(this->getStartingPoint().getX())).append("\" ");
	svgRepresentation.append("y1=\"").append(to_string(this->getStartingPoint().getY())).append("\" ");
	svgRepresentation.append("x2=\"").append(to_string(this->getEndPoint().getX())).append("\" ");
	svgRepresentation.append("y2=\"").append(to_string(this->getEndPoint().getY())).append("\" ");
	svgRepresentation.append("fill=\"").append(this->getColor()).append("\" ");

	svgRepresentation.append("/>");

	return svgRepresentation;
}

Point Line::getEndPoint() const
{
	return this->endPoint;
}

void Line::setEndPoint(Point endPoint)
{
	this->endPoint = endPoint;
}
