#ifndef INCLUDE_KRUSKAL_H
#define INCLUDE_KRUSKAL_H

#include "graph.h"
#include "edge.h"
#include <vector>

class Kruskal
{
	public:
		Kruskal(const Graph& g);
		std::vector<Edge> mst();
		double totalWeight() const;
		void print() const;
	private:
		std::vector<Edge> d_mst;
		double d_totalWeight;
};

#endif
