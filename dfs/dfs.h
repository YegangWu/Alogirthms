#include "graph_basic.h"
#include <vector>

class DFS
{
	private:
		int N;
		std::vector<bool> marked;
		std::vector<int> visitedNodes;
	public:
		DFS(int N);
		void dfs(const Graph& g, int v);
		void printPath();
};  
