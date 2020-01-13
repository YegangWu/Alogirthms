#ifndef INCLUDE_LINE_SEGMENT_H
#define INCLUDE_LINE_SEGMENT_H

#include "line_tree.h"
#include <queue>
#include <string>

class LineSegment
{
	public:
		LineSegment(const std::string& file);
		void sweepSearch();
	private:
		std::vector<Line> d_intersects;
		std::priority_queue<Line, std::vector<Line>, CompByX> d_queue;
};

#endif
