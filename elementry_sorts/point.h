#ifndef INCLUDE_POINT_H
#define INCLUDE_POINT_H

#include <iostream>

struct Point
{
	Point();
	Point(int x, int y);
	double x;
	double y;
};

inline
Point::Point(): x(0), y(0)
{
}

inline
Point::Point(int x, int y): x(x), y(y) 
{
}

inline
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

#endif
