#include "GeometryUtils.h"

double GeometryUtils::getDistance(Point from, Point to)
{
	return sqrt((from.getX() - to.getX()) * (from.getX() - to.getX()) +
				(from.getY() - to.getY()) * (from.getY() - to.getY()));
}

bool GeometryUtils::isInsideRectangle(const Point & point, const Rectangle & second)
{
	bool pointXInside = point.getX() >= second.getStartingPoint().getX() &&
		point.getX() <= second.getStartingPoint().getX() + second.getWidth();

	bool pointYInside = point.getY() >= second.getStartingPoint().getY() &&
		point.getY() <= second.getStartingPoint().getY() + second.getHeight();

	return pointXInside && pointYInside;
}

bool GeometryUtils::isInsideRectangle(const Rectangle & first, const Rectangle & second)
{
	Point startPoint = first.getStartingPoint();
	Point endPoint = first.getStartingPoint();
	endPoint.setX(endPoint.getX() + first.getWidth());
	endPoint.setY(endPoint.getY() + first.getHeight());

	return isInsideRectangle(startPoint, second) && isInsideRectangle(endPoint, second);
}

bool GeometryUtils::isInsideRectangle(const Circle & circle, const Rectangle & rect2)
{
	if (!isInsideRectangle(circle.getStartingPoint(), rect2))
		return false;

	Point rectStartPoint = rect2.getStartingPoint();
	Point circleStartPoint = circle.getStartingPoint();

	int xLeftOffset = circleStartPoint.getX() - rectStartPoint.getX();
	int xRightOffset = rectStartPoint.getX() + rect2.getWidth() - circleStartPoint.getX();
	int yDownOffset = circleStartPoint.getY() - rectStartPoint.getY();
	int yUpOffset = rectStartPoint.getY() + rect2.getHeight() - circleStartPoint.getY();

	int xMinValue = xLeftOffset < xRightOffset ? xLeftOffset : xRightOffset;
	int yMinValue = yDownOffset < yUpOffset ? yDownOffset : yUpOffset;
	int minValue = xMinValue < yMinValue ? xMinValue : yMinValue;

	return minValue >= circle.getRadius();
}

bool GeometryUtils::isInsideRectangle(const Line & first, const Rectangle & second)
{
	return isInsideRectangle(first.getStartingPoint(), second) &&
		   isInsideRectangle(first.getEndPoint(), second);
}

bool GeometryUtils::isInsideCircle(const Rectangle & first, const Circle & second)
{
	Point topLeft = first.getStartingPoint();
	Point bottomRight = first.getStartingPoint();
	bottomRight.setX(bottomRight.getX() + first.getWidth());
	bottomRight.setY(bottomRight.getY() + first.getHeight());

	return getDistance(topLeft, second.getStartingPoint()) <= second.getRadius() * 1.0 &&
		getDistance(bottomRight, second.getStartingPoint()) <= second.getRadius() * 1.0;
}

bool GeometryUtils::isInsideCircle(const Circle & first, const Circle & second)
{
	double radiusesDistance = getDistance(first.getStartingPoint(), second.getStartingPoint());

	return radiusesDistance <= abs(first.getRadius() - second.getRadius()) * 1.0;
}

bool GeometryUtils::isInsideCircle(const Line & first, const Circle & second)
{
	return getDistance(first.getStartingPoint(), second.getStartingPoint()) <= second.getRadius() * 1.0 &&
		getDistance(first.getEndPoint(), second.getStartingPoint()) <= second.getRadius() * 1.0;
}
