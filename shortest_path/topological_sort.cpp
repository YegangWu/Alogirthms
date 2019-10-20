#include "topological_sort.h"
#include "diag.h"
#include "graph.h"
#include <limits>
#include <iostream>

TopologicalSort::TopologicalSort(const Graph& g, int s)
{
	d_N = g.size();
	d_source = s;
	double infinity = std::numeric_limits<double>::infinity();
	Edge tmpEg(0,0,0);
	for(int i = 0; i < d_N; ++i)
	{
		d_distTo.push_back(infinity);
		d_pathTo.push_back(tmpEg);
	}
	d_distTo[s] = 0;
	d_pathTo[s] = Edge(s, s, 0);

	DIAG diag(g);
	diag.printDiagOrder();		
	std::vector<int> diagOrder = diag.order();
	for(size_t i = 0; i < diagOrder.size(); ++i)
	{
		int v = diagOrder[i];
		std::vector<Edge> edges;
		g.edgeFrom(edges, v);
		for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			relax(*iter);
		}
	}
}

void TopologicalSort::relax(const Edge& edge)
{
	int v = edge.from();
	int w = edge.to();
	double weight = edge.weight();
	if(d_distTo[w] > d_distTo[v] + weight)
	{
		d_distTo[w] = d_distTo[v] + weight;
		d_pathTo[w] = edge;
	}
}

std::stack<Edge> TopologicalSort::pathTo(int w)
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

void TopologicalSort::print()
{
	std::cout << "The shortest path from " << d_source << " to" << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << i << " is " << d_distTo[i] << ": ";
		std::stack<Edge> path = pathTo(i);
		while(!path.empty())
		{
			Edge edge = path.top();
			path.pop();
			std::cout << edge.from() << "->" << edge.to() << "(" << edge.weight() << "), ";
		}
		std::cout << std::endl;
	}
}
