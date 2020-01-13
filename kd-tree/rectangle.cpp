#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(double xLow, double yLow, double xHigh, double yHigh): xLow(xLow), yLow(yLow), xHigh(xHigh), yHigh(yHigh)
{
}

bool Rectangle::less(Node& node) const
{
	if(node.level%2 == 0)
	{
		std::cout << "compare x with point (" << node.x << ", " << node.y << ")" << std::endl;
		return xHigh < node.x;
	}
	else
	{
		std::cout << "compare y with point (" << node.x << ", " << node.y << ")" << std::endl;
		return yHigh < node.y;
	}
}

bool Rectangle::greater(Node& node) const
{
	if(node.level%2 == 0)
	{
		std::cout << "compare x with point (" << node.x << ", " << node.y << ")" << std::endl;
		return xLow > node.x;
	}
	else
	{
		std::cout << "compare y with point (" << node.x << ", " << node.y << ")" << std::endl;
		return yLow > node.y;
	}
}

bool Rectangle::inbetween(Node& node) const
{
	if(node.level%2 == 0)
	{
		std::cout << "compare x with point (" << node.x << ", " << node.y << ")" << std::endl;
		return node.x > xLow && node.x < xHigh;
	}
	else
	{
		std::cout << "compare y with point (" << node.x << ", " << node.y << ")" << std::endl;
		return node.y > yLow && node.y < yHigh;
	}
}

bool Rectangle::contain(Node& node) const
{
	return node.x > xLow && node.x < xHigh && node.y > yLow && node.y < yHigh;
}
