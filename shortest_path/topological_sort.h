#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "graph.h"
#include <stack>

class TopologicalSort
{
	public:
		TopologicalSort(const Graph& g, int s);
		void print();
	private:
		int d_N;
		int d_source;
		std::vector<double> d_distTo;
		std::vector<Edge> d_pathTo;
		void relax(const Edge& edge);

		std::stack<Edge> pathTo(int w);
};

#endif
