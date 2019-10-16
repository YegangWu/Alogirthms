#ifndef INCLUDE_BIPARTIE_H
#define INCLUDE_BIPARTIE_H

#include "graph_basic.h"
#include <vector>
#include <queue>

class BP
{
	public:
		BP(const Graph& g);
		void report();
	private:
		int d_N;
		std::vector<char> d_color;
		bool d_isBipartite;
		std::queue<int> q;
		bool dfs(const Graph& g, int v, char c);
		bool bfs(const Graph& g, int v, char c);
		char getReverse(char c);
};

#endif
