#include "scc.h"
#include "diag.h"
#include <iostream>

SCC::SCC(const Graph& g)
{
	d_N = g.size();
	d_count = 0;
	for(size_t i = 0; i < g.size(); ++i)
	{
		d_marked.push_back(false);
		d_clusterId.push_back(0);
	}
	Graph rG(g.reverseGraph());
	rG.print();
	DIAG diag(rG);
	std::vector<int> diagOrder = diag.diagOrder();
	for(std::vector<int>::reverse_iterator iter = diagOrder.rbegin(); iter != diagOrder.rend(); ++iter)
	{
		int v = *iter;
		if(!d_marked[v])
		{
			dfs(g, v, d_count);
			d_count++;
		}
	}
}

void SCC::dfs(const Graph& g, int v, int id)
{
	d_marked[v] = true;
	d_clusterId[v] = id;
	std::vector<int> edges;
	g.edgeFrom(edges, v);
	for(std::vector<int>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
	{
		int w = *iter;
		if(!d_marked[w])
		{
			dfs(g, w, id);
		}
	}	
}

bool SCC::isConnected(int v, int w)
{
	if(v < 0 || v >= d_N || w < 0 || w >= d_N)
	{
		return false;
	}
	return d_clusterId[v] == d_clusterId[w];
}

int SCC::totalCount()
{
	return d_count;
}

void SCC::print()
{
	std::cout << "There are " << d_count << " clusters in total" << std::endl;
	std::cout << "The label for each node is: " << std::endl;
	for(size_t i = 0; i < d_clusterId.size(); ++i)
	{
		std::cout << i << ", " << d_clusterId[i] << std::endl;
	}
	std::cout << std::endl;
}
