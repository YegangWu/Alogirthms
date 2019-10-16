#ifndef INCLUDE_GRAPH_H
#define INCLUDE_GRAPH_H

#include <string>
#include <vector>
#include "node.h"

class Graph
{
	public:
		Graph(const std::string& file);
		int size();
		Node* edgeFrom(int v);
		void deleteEdge(int v, int w);
		void print();
	private:
		int d_N;
		std::vector<Node*> d_edgeList;		
};

#endif
