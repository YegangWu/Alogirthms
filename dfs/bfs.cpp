#include "bfs.h"
#include <iostream>

BFS::BFS(int n) : N(n) 
{
	for(int i = 0; i < n; ++i)
	{
		marked.push_back(false);
	}
}

void BFS::bfs(const Graph& g, int v)
{
	q.push(v);
	marked[v] = true;
	while(!q.empty())
	{
		int w = q.front();
		visitedNodes.push_back(w);
		q.pop();

		std::vector<int> edges;
		g.edgeFrom(edges, w);
		for(std::vector<int>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			int x = *iter;
			if(!marked[x])
			{	
				q.push(x);
				marked[x] = true;
			}
		}
	}
}

void BFS::print()
{
	std::cout << "Nodes traveled by bfs: " << std::endl;
	for(std::vector<int>::const_iterator iter = visitedNodes.begin(); iter != visitedNodes.end(); ++iter)
	{
		std::cout << *iter << ", ";
	}
	std::cout << std::endl;
}
