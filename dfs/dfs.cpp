#include "dfs.h"
#include<iostream>
#include<string>

DFS::DFS(int n)
{
	N = n;
	for(int i = 0; i < n; ++i)
	{
		marked.push_back(false);
	}
}

void DFS::dfs(const Graph& g, int v)
{
	if( v < 0 || v >= N)
	{
		std::cerr << "vertex " << v << " is not in the graph!" << std::endl;
		return;
	}
	if( !marked[v] )
	{
		marked[v] = true;
		visitedNodes.push_back(v);
		std::vector<int> edges;
		g.edgeFrom(edges, v);
		for(std::vector<int>::const_iterator it = edges.begin(); it != edges.end(); ++it)
		{
			int w = *it;
			dfs(g, w);
		}
	}
}

void DFS::printPath()
{
	std::cout << "dfs path is " << std::endl;
	std::string delim("");
	for(size_t i = 0; i < visitedNodes.size(); ++i)
	{
		std::cout << delim << visitedNodes[i];
		delim = ", ";
	}
	std::cout << std::endl;
}
