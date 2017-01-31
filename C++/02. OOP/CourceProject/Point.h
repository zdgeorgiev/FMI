#ifndef POINT_HEADER_INCLUDED
#define POINT_HEADER_INCLUDED

#include <iostream>

using namespace std;

struct Point
{
public:
	Point(int x, int y);
	Point();
	~Point();
	Point(const Point& rhs);

	Point& operator=(const Point& rhs);

	void setX(int x);
	void setY(int y);

	int getX() const;
	int getY() const;

private:
	int x, y;
};

#endif