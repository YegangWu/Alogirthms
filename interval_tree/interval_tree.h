#ifndef INCLUDE_INTERVAL_TREE_H
#define INCLUDE_INTERVAL_TREE_H

#include "red_black_tree.h"
#include <iostream>
#include <queue>
#include <string>

struct Line
{
	int id;
	double lo;
	double hi;
	double x;
	double max;
	bool start;
	Line(int id, double lo, double hi, double x, double max, bool start);
};

inline
bool operator==(const Line& lhs, const Line& rhs)
{
	return lhs.lo == rhs.lo;
}

inline
bool operator<(const Line& lhs, const Line& rhs)
{
	return lhs.lo < rhs.lo;
}

inline
bool operator>(const Line& lhs, const Line& rhs)
{
	return lhs.lo > rhs.lo;
}

inline
bool operator>=(const Line& lhs, const Line& rhs)
{
	return lhs.lo >= rhs.lo;
}

inline
std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "(" << line.lo << ", " << line.hi << "[" << line.max << "])";
	return os;
}


class CompByX
{
	public:
		bool operator()(const Line& lhs, const Line& rhs)
		{
			return lhs.x > rhs.x;
		}
};

class IntervalTree: public RedBlackTree<Line>
{
	public:
		IntervalTree(const std::string& filename);
		virtual void put(Line key, int v);
		void sweep();
		void searchOverlaps(const Line& line, std::vector<int>& overlaps);
	private:
		Node<Line>* put(Node<Line>* root, Line key, int v, int rank);
		std::priority_queue<Line, std::vector<Line>, CompByX> d_queue;

		void searchOverlaps(Node<Line>* root, const Line& line, std::vector<int>& overlaps);
};

#endif
