#ifndef INCLUDE_FLOW_GRAPH_H
#define INCLUDE_FLOW_GRAPH_H

#include "edge.h"
#include <string>
#include <vector>

class FlowGraph
{
	public:
		FlowGraph(const std::string& filename);
		std::vector<Edge*> edgeFrom(int v) const;
		int size() const;
		void print() const;
	private:
		int d_N;
		std::vector<std::vector<Edge*> > d_edgeList;
};

#endif
