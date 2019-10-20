#include "diag.h"
#include <iostream>
#include <algorithm>

DIAG::DIAG(const Graph& g)
{
	d_N = g.size();
	for(int i = 0; i < d_N; ++i)
	{
		d_marked.push_back(false);
	}
	for(int i = 0; i < d_N; ++i)
	{
		if(!d_marked[i])
		{
			dfs(g, i);
		}
	}	
	std::reverse(d_visited.begin(), d_visited.end());
}

void DIAG::dfs(const Graph& g, int v)
{
	d_marked[v] = true;
	std::vector<Edge> edges;
	g.edgeFrom(edges, v);
	for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
	{
		int w = iter->to();
		if(!d_marked[w])
		{
			dfs(g, w);
		}
	}
	d_visited.push_back(v);
}

std::vector<int> DIAG::order() const
{
	return d_visited;
}

void DIAG::printDiagOrder() const
{
	for(size_t i = 0; i < d_visited.size(); ++i)
	{
		std::cout << d_visited[i] << ", ";
	}
	std::cout << std::endl;
}

