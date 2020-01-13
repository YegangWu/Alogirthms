#ifndef INCLUDE_KD_TREE
#define INCLUDE_KD_TREE

#include <string>
#include <cmath>
#include <vector>
#include "rectangle.h"

struct Node
{
	double x;
	double y;
	int level;
	Node* left;
	Node* right;
	Node(double x, double y, int level);
};

inline
bool operator<(const Node& lhs, const Node& rhs)
{
	if(rhs.level%2 == 0)
	{
		return lhs.x < rhs.x;
	}
	else
	{
		return lhs.y < rhs.y;
	}
}

inline
bool operator>(const Node& lhs, const Node& rhs)
{
	if(rhs.level%2 == 0)
	{
		return lhs.x > rhs.x;
	}
	else
	{
		return lhs.y > rhs.y;
	}
}

inline
double operator-(const Node& lhs, const Node& rhs)
{
	if(rhs.level%2 == 0)
	{
		return std::abs(lhs.x - rhs.x); 
	}
	else
	{
		return std::abs(lhs.y - rhs.y);
	}
}

class Rectangle;
class KDTree
{
	public:
		KDTree();
		KDTree(const std::string& filename);
		void put(Node& node);
		void print();
		Node* nearestNeighbor(Node& node, double* dist);
		void pointsInRegion(const Rectangle& rec);
	private:
		Node* d_root;
		Node* put(Node* root, Node& node, int level);
		void print(Node* node);
		double alternativeMinDist(Node* root, Node* parent, Node& node);
		void exploreChildren(Node* root, Node& node, Node** child, Node** sibling);
		Node* nearestNeighbor(Node* root, Node* parent, Node& node, double* dist);
		void pointsInRegion(Node* root, const Rectangle& rec, std::vector<Node>& points);
};



#endif
