#include "dijkstra.h"
#include <limits>
#include <iostream>

Dijkstra::Dijkstra(const Graph& g, int s)
{
	d_N = g.size();
	d_source = s;
	double infinity = std::numeric_limits<double>::infinity();
	Edge tmpEg(0,0,0);
	for(int i = 0; i < d_N; ++i)
	{
		d_distTo.push_back(infinity);
		d_pathTo.push_back(tmpEg);
		d_marked.push_back(false);
	}
	d_distTo[s] = 0;
	
	Node node(s, 0);
	d_pq.push(node);
	while(!d_pq.empty())
	{
		Node node = d_pq.top();
		d_pq.pop();
		int v = node.d_v;
		if(d_marked[v])
		{
			continue;
		}
		d_marked[v] = true;
		std::vector<Edge> edges;
		g.edgeFrom(edges, v);
		for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			int w = iter->to();
			if(!d_marked[w])
			{
				relax(*iter);
			}
		}
	}
}

void Dijkstra::relax(const Edge& edge)
{
	int v = edge.from();
	int w = edge.to();
	double weight = edge.weight();
	if(d_distTo[w] > d_distTo[v] + weight)
	{
		std::cout << "relax edge " << v << "->" << w << std::endl;
		d_distTo[w] = d_distTo[v] + weight;
		d_pathTo[w] = edge;
		Node node(w, d_distTo[w]);
		d_pq.push(node);
	}
}

std::stack<Edge> Dijkstra::getPathTo(int w) const
{
	std::stack<Edge> path;
	Edge edge = d_pathTo[w];
	int v = edge.from();
	while(v != d_source)
	{
		path.push(edge);
		edge = d_pathTo[v];
		v = edge.from();
	}
	path.push(edge);
	return path;
}

void Dijkstra::print() const
{
	std::cout << "From source " << d_source << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << "shortest path to " << i << " is " << d_distTo[i] << ": ";
		std::stack<Edge> path = getPathTo(i);
		while(!path.empty())
		{
			Edge edge = path.top();
			std::cout << edge.from() << "->" << edge.to() << "(" << edge.weight() << "), ";
			path.pop();
		}
		std::cout << std::endl;
	}	
}
