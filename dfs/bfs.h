#ifndef INCLUDE_BFS_H
#define INCLUDE_BFS_H

#include <vector>
#include <queue>
#include "graph_basic.h"

class BFS
{
	public:
		BFS(int n);
		void bfs(const Graph& g, int v);
		void print();
	private:
		std::vector<bool> marked;
		std::queue<int> q;
		std::vector<int> visitedNodes;
		int N;
};

#endif
