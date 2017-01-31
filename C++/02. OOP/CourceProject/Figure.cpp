#include "Figure.h"

Figure::Figure(string name, Point startPoint, string color, string svgTag)
{
	this->startPoint = startPoint;
	this->setName(name);
	this->setColor(color);
	this->setSVGTag(svgTag);
}

Figure::Figure()
{
	this->startPoint = Point();
	this->setName(".");
	this->setColor(".");
	this->setSVGTag(".");
}

Figure::~Figure()
{
	this->name.clear();
	this->color.clear();
	this->svgTag.clear();
}

Figure::Figure(const Figure & rhs)
{
	this->startPoint = rhs.startPoint;
	this->setName(rhs.name);
	this->setColor(rhs.color);
	this->setSVGTag(rhs.svgTag);
}

Figure & Figure::operator=(const Figure & rhs)
{
	if (this != &rhs)
	{
		this->startPoint = rhs.startPoint;
		this->setName(rhs.name);
		this->setColor(rhs.color);
		this->setSVGTag(rhs.svgTag);
	}

	return *this;
}

string Figure::toSVGString() const
{
	return "Basic figure dont have SVG string representation.";
}

void Figure::print() const
{
	cout << this->name << " " << this->color << " " << this->startPoint.getX() << " " << this->startPoint.getY();
}

void Figure::translate(int horizontal, int vertical)
{
	this->startPoint.setX(this->startPoint.getX() + horizontal);
	this->startPoint.setY(this->startPoint.getY() + vertical);
}

Point Figure::getStartingPoint() const
{
	return this->startPoint;
}

string Figure::getName() const
{
	return this->name;
}

string Figure::getColor() const
{
	return this->color;
}

string Figure::getSVGTag() const
{
	return this->svgTag;
}

void Figure::setName(string name)
{
	if (name.empty())
		cout << "Figure name cannot be empty" << endl;
	else
		this->name = name;
}

void Figure::setColor(string color)
{
	if (color.empty())
		cout << "Figure color cannot be empty" << endl;
	else
		this->color = color;
}

void Figure::setSVGTag(string svgTag)
{
	if (svgTag.empty())
		cout << "Figure svg tag cannot be empty" << endl;
	else
		this->svgTag = svgTag;
}
