#ifndef INCLUDE_DIAG_H
#define INCLUDE_DIAG_H

#include "graph.h"
#include <vector>

class DIAG
{
	public:
		DIAG(const Graph& g);
		std::vector<int> order() const;
		void printDiagOrder() const;
	private:
		int d_N;
		std::vector<bool> d_marked;
		std::vector<int> d_visited;	

		void dfs(const Graph& g, int v);
};

#endif
