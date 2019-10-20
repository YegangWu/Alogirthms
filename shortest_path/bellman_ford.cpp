#include "bellman_ford.h"
#include <limits>
#include <iostream>

BellmanFord::BellmanFord(const Graph&g, int s)
{
	d_N = g.size();
	d_source = s;
	d_hasNegativeCycle = false;
	Edge tmpEg(0, 0, 0);
	double infinity = std::numeric_limits<double>::infinity();
	for(int i = 0; i < d_N; ++i)
	{
		d_distTo.push_back(infinity);
		d_pathTo.push_back(tmpEg);
	}
	d_distTo[s] = 0;
	d_pathTo[s] = Edge(s, s, 0);

	for(int i = 0; i < d_N; ++i)
	{
		for(int v = 0; v < d_N; ++v)
		{
			std::vector<Edge> edges;
			g.edgeFrom(edges, v);
			for(std::vector<Edge>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
			{
				relax(*iter, i);
			}
		}
	}
	if(d_hasNegativeCycle)
	{
		reconstructNgCycle();
	}
}

void BellmanFord::relax(const Edge& edge, int repeats)
{
	int v = edge.from();
	int w = edge.to();
	double weight = edge.weight();
	if(d_distTo[w] > d_distTo[v] + weight)
	{
		d_distTo[w] = d_distTo[v] + weight;
		d_pathTo[w] = edge;
		if(repeats == d_N-1)
		{
			d_hasNegativeCycle = true;
			d_cycleEndNode = v;
			std::cout << "Found negative cycle in " << v << std::endl;
		}
	}
}

bool BellmanFord::hasNegativeCycle() const
{
	return d_hasNegativeCycle;
}

void BellmanFord::reconstructNgCycle()
{
	std::cout << "reconstruct negative cycle" << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << d_pathTo[i].from() << "->" << d_pathTo[i].to() << std::endl;
	}
	std::cout << std::endl;
	bool marked[d_N];
	for(int i = 0; i < d_N; ++i)
	{
		marked[i] = false;
	}
	std::stack<Edge> st;
	int w = d_cycleEndNode;
	Edge edge = d_pathTo[w];
	while( !marked[w] )
	{
		std::cout << edge.from() << "->" << edge.to() << std::endl;
		std::cout << "mark " << w << std::endl;
		marked[w] = true;
		st.push(edge);
		w = edge.from();
		edge = d_pathTo[w];
	}
	st.push(edge);
	std::cout << "last edge is " << edge.from() << "->" << edge.to() << std::endl;
	std::cout << "last node w is " << w << std::endl;
	while(!st.empty() && edge.from() != w)
	{
		edge = st.top();
		d_ngCycleEdges.push_back(edge);
		st.pop();
	}
	d_ngCycleEdges.push_back(edge);
	std::cout << "Finish reconstruct negative cycle" << std::endl;
}

std::vector<Edge> BellmanFord::negativeCycles() const
{
	return d_ngCycleEdges;
}

std::stack<Edge> BellmanFord::pathTo(int w) const
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

void BellmanFord::print() const
{
	if(d_hasNegativeCycle)
	{
		std::cout << "There is at least one negative cycle:" << std::endl;
		for(std::vector<Edge>::const_iterator iter = d_ngCycleEdges.begin(); iter != d_ngCycleEdges.end(); ++iter)
		{
			std::cout << iter->from() << "->" << iter->to() << "(" << iter->weight() << "), ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "There are not negative cycles." << std::endl;
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
}
