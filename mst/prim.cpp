#include "prim.h"
#include "edge.h"
#include <iostream>

Prim::Prim(const Graph& g)
{
	d_N = g.size();
	for(int i = 0; i < d_N; ++i)
	{
		d_marked.push_back(false);
	}	
	visit(g, 0);
	while( !d_pq.empty() || d_mst.size() < d_N -1 )
	{
		Edge edge = d_pq.top();
		d_pq.pop();
		int v = edge.either();
		int w = edge.other(v);
		if(d_marked[v] && d_marked[w])
		{
			continue;
		}

		d_mst.push_back(edge);
		d_totalWeight += edge.weight();
		if(!d_marked[v])
		{
			visit(g, v);
		}
		else
		{
			visit(g, w);
		}
	}
}

void Prim::visit(const Graph& g, int v)
{
	d_marked[v] = true;
	std::vector<Edge> edges;
	g.edgeFrom(edges, v);
	for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
	{
		int w = iter->other(v);
		if(!d_marked[w])
		{
			d_pq.push(*iter);
		}
	}
}

void Prim::print() const
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
