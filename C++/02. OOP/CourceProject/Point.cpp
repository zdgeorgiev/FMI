#include "Point.h"

Point::Point(int x, int y)
{
	this->setX(x);
	this->setY(y);
}

Point::Point()
{
	this->x = -1;
	this->y = -1;
}

Point::~Point()
{
	this->x = -1;
	this->y = -1;
}

Point::Point(const Point & rhs)
{
	this->x = rhs.getX();
	this->y = rhs.getY();
}

Point & Point::operator=(const Point & rhs)
{
	if (this != &rhs)
	{
		this->x = rhs.getX();
		this->y = rhs.getY();
	}

	return *this;
}

void Point::setX(int x)
{
	this->x = abs(x);
}

void Point::setY(int y)
{
	this->y = abs(y);
}

int Point::getX() const
{
	return this->x;
}

int Point::getY() const
{
	return this->y;
}
