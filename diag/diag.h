#ifndef INCLUDE_DIAG_H
#define INCLUDE_DIAG_H

#include "graph_basic.h"
#include <vector>

class DIAG
{
	public:
		DIAG(const Graph& g);
		std::vector<int> diagOrder();
		void printDiagOrder();
	private:
		int d_N;
		std::vector<bool> d_marked;
		std::vector<int> d_visitedNode;
		void dfs(const Graph& g, int v);
};	

#endif
