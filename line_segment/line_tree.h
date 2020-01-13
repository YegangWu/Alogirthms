#ifndef INCLUDE_LINE_TREE
#define INCLUDE_LINE_TREE

#include "red_black_tree.h"
#include <vector>
#include <iostream>

enum LineType 
{
	HORIZONTAL,
	VERTICAL
};

struct Line 
{
	int d_id;
	double d_x1;
	double d_x2;
	double d_y1;
	double d_y2;
	LineType d_type;	
	Line(int d, double x1, double x2, double y1, double y2, LineType type);
};

inline
bool operator<(const Line& l1, const Line& l2)
{
	return l1.d_y1 < l2.d_y1;
}

inline 
bool operator>(const Line& l1, const Line& l2)
{
	return l1.d_y1 > l2.d_y1;
}

inline 
bool operator==(const Line& l1, const Line& l2)
{
	return l1.d_y1 == l2.d_y1;
}


inline 
bool operator>=(const Line& l1, const Line& l2)
{
	return l1.d_y1 >= l2.d_y1;
}


inline
std::ostream& operator<<(std::ostream& ss, const Line& line)
{
	ss << line.d_id << ", " 
	   << line.d_type << ", "
	   << line.d_x1 << ", "
	   << line.d_x2 << ", "
	   << line.d_y1 << ", "
	   << line.d_y2 << ", ";
	return ss;
}


class CompByX
{
public:
	bool operator()(const Line& l1, const Line& l2)
	{
		return l1.d_x1 > l2.d_x1;
	}
};

class LineTree: public RedBlackTree<Line>
{
	public:
		LineTree();
		std::vector<Line> range(double lo, double hi);	
	private:
		void range(Node<Line>* root, double lo, double hi, std::vector<Line>& lines);
};

#endif
