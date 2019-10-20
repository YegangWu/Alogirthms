#ifndef INCLUDE_BELLMAN_FORD_H
#define INCLUDE_BELLMAN_FORD_H

#include "graph.h"
#include <vector>
#include <stack>

class BellmanFord
{
	public:
		BellmanFord(const Graph& g, int s);
		bool hasNegativeCycle() const;
		std::vector<Edge> negativeCycles() const;
		void print() const;
	private:
		int d_source;
		int d_N;
		std::vector<double> d_distTo;
		std::vector<Edge> d_pathTo;
		bool d_hasNegativeCycle; //detect negative cycle
		int d_cycleEndNode; //There can be multiple negative cycles, but for simplicity, we only return one such cycle
		std::vector<Edge> d_ngCycleEdges;
		
		void relax(const Edge& edge, int repeats);	
		std::stack<Edge> pathTo(int w) const;
		void reconstructNgCycle();
};

#endif
