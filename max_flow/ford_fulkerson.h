#ifndef INCLUDE_FORD_FULKERSON_H
#define INCLUDE_FORD_FULKERSON_H

#include "flow_graph.h"

class FordFulkerson
{
	public:
		FordFulkerson(FlowGraph& g, int s, int t);
		void print(const FlowGraph& g) const;
	private:
		int d_N;
		int d_source;
		int d_target;
		double d_maxFlow;
		std::vector<Edge*> d_pathTo;
		std::vector<bool> d_marked;

		bool hasResidualPath(const FlowGraph& g);
		void dfs(const FlowGraph& g, int v);
		void bfs(const FlowGraph& g, int v);
};

#endif
