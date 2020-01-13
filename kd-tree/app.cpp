#include "kd_tree.h"
#include <iostream>

void testNearestNeighbors()
{
	//KDTree kdtree("data.txt");
	//Node node(90, 88, 0);
	KDTree kdtree("data2.txt");
	Node node(1, 11, 0);
	double nearestDist;
	Node* nearestNeighbor = kdtree.nearestNeighbor(node, &nearestDist);
	std::cout << "Near point is (" << nearestNeighbor->x << ", " << nearestNeighbor->y << "), dist: " << nearestDist << std::endl; 
}

void testPointsInRectangle()
{
	KDTree kdtree("data2.txt");
	Rectangle rec(4, 2, 10, 10);
	kdtree.pointsInRegion(rec); 
}

int main()
{
	testPointsInRectangle();
	return 0;	
}
