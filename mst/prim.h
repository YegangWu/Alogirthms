#ifndef INCLUDE_PRIM_H
#define INCLUDE_PRIM_H

#include "graph.h"
#include "edge.h"
#include <queue>

class Prim
{
	public:
		Prim(const Graph& g);
		void print() const;
	private:
		int d_N;
		std::vector<bool> d_marked;
		std::priority_queue<Edge, std::vector<Edge>, greaterByWeight> d_pq;
		std::vector<Edge> d_mst;	
		double d_totalWeight;
		void visit(const Graph& g, int v);
};

#endif
