#include "kruskal.h"
#include "graph.h"
#include "uf.h"
#include <queue>
#include <iostream>

Kruskal::Kruskal(const Graph& g)
{
	int N = g.size();
	d_totalWeight = 0;
	std::priority_queue<Edge, std::vector<Edge>, greaterByWeight> pq;
	for(int i = 0; i < N; ++i)
	{
		std::vector<Edge> edges;
		g.edgeFrom(edges, i);
		for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			int v = iter->either();
			int w = iter->other(v);
			if(v < w)
			{
				pq.push(*iter);	
			}
		}
	}
	UF uf(N);
	while(!pq.empty() || d_mst.size() < N-1)
	{
		Edge eg = pq.top();
		pq.pop();
		int v = eg.either();
		int w = eg.other(v);
		if(!uf.connected(v, w))
		{
			uf.connect(v, w);
			d_mst.push_back(eg);
			d_totalWeight += eg.weight();
		}
	}
}

std::vector<Edge> Kruskal::mst()
{
	return d_mst;
}

void Kruskal::print() const
{
	std::cout << "Minimal spanning tress contains the following edges: " << std::endl;
	for(std::vector<Edge>::const_iterator iter = d_mst.begin(); iter != d_mst.end(); ++iter)
	{
		int v = iter->either();
		int w = iter->other(v);
		double weight = iter->weight();
		std::cout << v << " " << w << " " << weight << std::endl;
	}
	std::cout << "Its total weight is " << d_totalWeight << std::endl;
}
