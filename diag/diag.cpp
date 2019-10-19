#include "diag.h"
#include <iostream>

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
}

void DIAG::dfs(const Graph& g, int v)
{
	d_marked[v] = true;
	std::vector<int> edgeList;
	g.edgeFrom(edgeList, v);
	for(std::vector<int>::const_iterator iter = edgeList.begin(); iter != edgeList.end(); ++iter)
	{
		int w = *iter;
		if(!d_marked[w])
		{
			dfs(g, w);
		}
	}
	d_visitedNode.push_back(v);
}

std::vector<int> DIAG::diagOrder()
{
	return d_visitedNode;
}

void DIAG::printDiagOrder()
{
	std::cout << "DIAG order of graph nodes is: " << std::endl;
	for(std::vector<int>::reverse_iterator iter = d_visitedNode.rbegin(); iter != d_visitedNode.rend(); ++iter)
	{
		std::cout << *iter << ", ";
	}
	std::cout << std::endl;
}
