#include "Point.h"

Point::Point(int x, int y) :
	x(x), y(y)
{
}

void Point::operator+=(const Point& other)
{
	x += other.x;
	y += other.y;
}

Point Point::operator+(const Point& other)
{
	return Point{ x + other.x, y + other.y };
}

Point Point::operator*(int val)
{
	return Point{ x*val, y*val };
}
