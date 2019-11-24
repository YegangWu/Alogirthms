#include "convex_hull.h"
#include "shell_sort.h"
#include <fstream>
#include <iostream>

ConvexHull::ConvexHull(const std::string& file)
{
	std::ifstream infile(file);
	double x, y;
	while(infile >> x >> y)
	{
		d_points.push_back(Point(x, y));
	}
}

void ConvexHull::search()
{
	LessThanByY lessy;
	ShellSort<Point, LessThanByY> shellsortY(d_points, lessy);
	shellsortY.sort();
	//print(d_points);

	std::vector<Point>::const_iterator first = d_points.begin() + 1;
	std::vector<Point>::const_iterator end = d_points.end();
	std::vector<Point> points(first, end);
	LessThanByPolar lessp(d_points[0]);
	ShellSort<Point, LessThanByPolar> shellsortP(points, lessp);
	shellsortP.sort();
	//print(points);	

	Point p1 = d_points[0];
	Point p2 = points[0];
	d_convexPoints.push(p1);
	d_convexPoints.push(p2);
	for(size_t i = 1; i < points.size(); ++i)
	{
		Point p3 = points[i];

		p2 = d_convexPoints.top();
		d_convexPoints.pop();
		while(! isConvex(p1, p2, p3))
		{
			p2 = p1;
			d_convexPoints.pop();
			p1 = d_convexPoints.top();
		}
		d_convexPoints.push(p2);
		d_convexPoints.push(p3);
		p1 = p2;
		p2 = p3;
	}
	printConvexPoints();	
}

bool ConvexHull::isConvex(const Point& p1, const Point& p2, const Point& p3)
{
	double area = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
	return area > 0;
}

void ConvexHull::print(const std::vector<Point>& list)
{
	for(size_t i = 0; i < list.size(); ++i)
	{
		std::cout << list[i] << std::endl;
	}
}

void ConvexHull::printConvexPoints()
{
	std::cout << "In printConvexPoints, size: " << d_convexPoints.size() << std::endl;
	while(!d_convexPoints.empty())
	{
		std::cout << d_convexPoints.top() << ", ";
		d_convexPoints.pop();
	}
	std::cout << std::endl;
}
