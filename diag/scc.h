#ifndef INCLUDE_SCC_H
#define INCLUDE_SCC_H

#include "graph_basic.h"

class SCC
{
	public:
		SCC(const Graph& g);
		bool isConnected(int v, int w);
		int totalCount();
		void print();
	private:
		int d_N;
		int d_count;
		std::vector<bool> d_marked;
		std::vector<int> d_clusterId;
		void dfs(const Graph& g, int v, int id);
};

#endif
