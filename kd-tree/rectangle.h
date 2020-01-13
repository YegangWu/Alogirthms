#ifndef INCLUDE_RECTANGLE_H
#define INCLUDE_RECTANGLE_H

#include "kd_tree.h"

struct Node;
class Rectangle
{
	public:
		Rectangle(double xLow, double yLow, double xHigh, double yHigh);
		bool less(Node& node) const;
		bool greater(Node& node) const;
		bool inbetween(Node& node) const;
		bool contain(Node& node) const;
	private:
		double xLow;
		double yLow;
		double xHigh;
		double yHigh;
};

#endif
