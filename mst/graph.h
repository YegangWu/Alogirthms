#ifndef INCLUDE_GRAPH_H
#define INCLUDE_GRAPH_H

#include "edge.h"
#include <string>
#include <vector>

class Graph
{
	public:
		Graph(const std::string& filename);
		bool edgeFrom(std::vector<Edge>& edges, int v) const;
		int size() const;
	private:
		std::vector<std::vector<Edge> > d_edgeList;
		int d_N;	
};

#endif
