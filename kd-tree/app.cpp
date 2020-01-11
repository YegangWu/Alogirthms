#include "kd_tree.h"
#include <iostream>

int main()
{
	//KDTree kdtree("data.txt");
	//Node node(90, 88, 0);
	KDTree kdtree("data2.txt");
	Node node(1, 11, 0);
	double nearestDist;
	Node* nearestNeighbor = kdtree.nearestNeighbor(node, &nearestDist);
	std::cout << "Near point is (" << nearestNeighbor->x << ", " << nearestNeighbor->y << "), dist: " << nearestDist << std::endl; 
	return 0;	
}
