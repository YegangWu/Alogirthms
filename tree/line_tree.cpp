#include "line_tree.h"

Line::Line(int id, double x1, double x2, double y1, double y2, LineType type): d_id(id), d_x1(x1), d_x2(x2), d_y1(y1), d_y2(y2), d_type(type)
{
}

LineTree::LineTree()
{
}

std::vector<Line> LineTree::range(double lo, double hi)
{
	std::vector<Line> lines;
	range(d_root, lo, hi, lines);
	return lines;
}

void LineTree::range(Node<Line>* root, double lo, double hi, std::vector<Line>& lines)
{
	if(root == NULL) {
		return;
	}
	if(root->key.d_y1 < lo) {
		range(root->right, lo, hi, lines);
	}
	else if(root->key.d_y1 > hi) {
		range(root->left, lo, hi, lines);
	}
	else {
		lines.push_back(root->key);
		range(root->left, lo, hi, lines);
		range(root->right, lo, hi, lines);
	}
}
