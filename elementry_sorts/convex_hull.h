#ifndef INCLDUE_CONVEX_HULL_H
#define INCLDUE_CONVEX_HULL_H

#include "point.h"
#include <string>
#include <cmath>
#include <stack>
#include <vector>

class ConvexHull
{
	public:
		ConvexHull(const std::string& file);
		void search();
	private:
		std::vector<Point> d_points;		
		std::stack<Point> d_convexPoints;
		
		bool isConvex(const Point& p1, const Point& p2, const Point& p3);
		void print(const std::vector<Point>& list);
		void printConvexPoints();
};

struct LessThanByY
{
	bool operator()(Point& p1, Point& p2)
	{
		return p1.y < p2.y;
	}
};

struct LessThanByPolar
{
	Point d_target;
	LessThanByPolar(const Point& target);

	bool operator()(const Point& p1, const Point& p2)
	{
		double dx1 = p1.x - d_target.x;
		double dy1 = p1.y - d_target.y;
		double dx2 = p2.x - d_target.x;
		double dy2 = p2.y - d_target.y;
		//In case they lie on difference y planes with respect to d_target, the one on positive y plance has smaller polar angle.
		if( dy1*dy2 < 0 )
		{
			return dy1 > dy2;
		}
		//In case they lie in the same y plane, compare their cosine values, bigger cosine value means smaller polar angle on positive y plane, and the opposite on negative y plane.
		else
		{
			double cosine1 = dx1/std::sqrt(dx1*dx1 + dy1*dy1);
			double cosine2 = dx2/std::sqrt(dx2*dx2 + dy2*dy2);
			double sign = dy1*(cosine1-cosine2);
			return sign > 0;
		}
	}
};

inline
LessThanByPolar::LessThanByPolar(const Point& target): d_target(target)
{
}

#endif
