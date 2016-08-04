#pragma once

class Point
{
public:
	Point() = delete;
	Point(int x, int y);

	void operator+=(const Point& other);
	Point operator+(const Point& other);
	Point operator*(int val);

public:
	int x;
	int y;
};