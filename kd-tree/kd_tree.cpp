#include "kd_tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

Node::Node(double x, double y, int level): x(x), y(y), level(level), left(NULL), right(NULL)
{
}

KDTree::KDTree(): d_root(NULL)
{
}

KDTree::KDTree(const std::string& filename): d_root(NULL)
{
	std::ifstream infile(filename);
	std::string line;
	double x, y;
	while(getline(infile, line))
	{
		std::cout << "read " << line << std::endl;
		std::stringstream ss(line);
		std::cout << "ss.str(): " << ss.str() << std::endl;
		ss >> x >> y;
		std::cout << "x: " << x << ", y: " << y << std::endl;
		Node node(x, y, 0);
		put(node);
	} 
	print();
}

void KDTree::put(Node& node)
{
	d_root = put(d_root, node, 0);
}

Node* KDTree::put(Node* root, Node& node, int level)
{
	if(root == NULL)
	{
		root = new Node(node.x, node.y, level);
		return root;
	}
	if(node < (*root))
	{
		root->left = put(root->left, node, level+1);
	}
	else
	{
		root->right = put(root->right, node, level+1);
	}
	return root;
}

void KDTree::print()
{
	print(d_root);
}

void KDTree::print(Node* node)
{
	if(node == NULL)
	{
		return;
	}
	print(node->left);
	std::cout << "(" << node->x << "," << node->y << "), ";
	print(node->right);
}

Node* KDTree::nearestNeighbor(Node& node, double* dist)
{
	*dist = std::numeric_limits<double>::infinity(); 
	return nearestNeighbor(d_root, NULL, node, dist);
}

void KDTree::exploreChildren(Node* root, Node& node, Node** child, Node** sibling)
{
	if(node < (*root))
	{
		*child = root->left;
		*sibling = root->right;
	}
	else
	{
		*child = root->right;
		*sibling = root->left;
	}
}

double KDTree::alternativeMinDist(Node* root, Node* parent, Node& node)
{
	if(parent == NULL)
	{
		double dist = root->x - node.x;
		return node < (*root) ? dist : -dist ;
	}
	if( (node < (*parent) && (*root) < (*parent))
		|| (node > (*parent) && (*root) > (*parent)) )
	{
		return node - *root;
	}
	else
	{
		double x, y;
		if(parent->level%2 == 0)
		{
			x = parent->x;
			y = root->y;
		}
		else
		{
			x = root->x;
			y = parent->y;
		}
		return std::sqrt(std::pow(node.x-x, 2) + std::pow(node.y-y, 2));
	}		
}

Node* KDTree::nearestNeighbor(Node* root, Node* parent, Node& node, double* dist)
{
	if(root == NULL)
	{
		*dist = std::numeric_limits<double>::infinity(); 
		std::cout << "no points in this region, will return infinity" << std::endl;
		return NULL;
	}
	double distCenter = std::sqrt(std::pow(node.x - root->x,2) + std::pow(node.y - root->y, 2));
	std::cout << "center point: (" << root->x << ", " << root->y <<  "), dist: " << distCenter << std::endl;

	Node* child;
	Node* sibling;
	exploreChildren(root, node, &child, &sibling);
		
	double distSameSide;
	Node* neighbor = nearestNeighbor(child, root, node, &distSameSide);
	std::cout << "center point: (" << root->x << ", " << root->y << "), distance on the same side: " << distSameSide << std::endl;

	double distOtherSide = alternativeMinDist(root, parent, node);
	std::cout << "minimum possible distance on the other side: " << distOtherSide << std::endl;
	if(distSameSide < distOtherSide)
	{
		assert(distSameSide < distCenter);
		*dist = distSameSide;
		return neighbor;
	}
	else
	{
		std::cout << "explore the other region" << std::endl;
		Node* alternativeNeighbor = nearestNeighbor(sibling, root, node, dist);
		std::cout << "center point: (" << root->x << ", " << root->y << "), distance on the other side: " << *dist << std::endl;
		if(distSameSide < *dist && distSameSide < distCenter)
		{
			*dist = distSameSide;
			return neighbor;
		}
		else if(*dist < distSameSide && *dist < distCenter)
		{
			return alternativeNeighbor;
		}
		else
		{
			*dist = distCenter;
			return root;
		}
	}
}

void KDTree::pointsInRegion(const Rectangle& rec)
{
	std::vector<Node> points;
	pointsInRegion(d_root, rec, points);
	for(size_t i = 0; i < points.size(); ++i)
	{
		std::cout << "(" << points[i].x << ", " << points[i].y << "), ";
	}
	std::cout << std::endl;
}

void KDTree::pointsInRegion(Node* root, const Rectangle& rec, std::vector<Node>& points)
{
	if(root == NULL)
	{
		return;
	}	
	if(rec.less(*root))
	{
		std::cout << "rec is on the left/buttom of point (" << root->x << ", " << root->y << ")" << std::endl;
		pointsInRegion(root->left, rec, points);
	}
	else if(rec.greater(*root))
	{
		std::cout << "rec is on the right/top of point (" << root->x << ", " << root->y << ")" << std::endl;
		pointsInRegion(root->right, rec, points);
	}
	else
	{
		std::cout << "rec is in between of point (" << root->x << ", " << root->y << ")" << std::endl;
		if(rec.contain(*root))
		{
			std::cout << "rec contains point (" << root->x << ", " << root->y << ")" << std::endl;
			points.push_back(*root);
		}
		pointsInRegion(root->left, rec, points);
		pointsInRegion(root->right, rec, points);
	}
}
