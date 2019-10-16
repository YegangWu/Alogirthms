#ifndef INCLUDE_CCOMPONENTS_H
#define INCLUDE_CCOMPONENTS_H

#include <vector>
#include "graph_basic.h"

class CC
{
	public:
		CC(const Graph& g);
		bool connected(int v, int w);
		int count();
		int id(int v);
		void printInfo();
	private:
		std::vector<int> idList;
		std::vector<bool> marked;
		int d_count;
		int d_N;
		void dfs(const Graph& g, int v, int clusterId);
};

#endif
