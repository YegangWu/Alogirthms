#include "digraph.h"
#include <iostream>

Digraph::Digraph(int N): d_N(N)
{
	for(int i = 0; i < d_N; ++i)
	{
		d_mark.push_back(false);
	}

	for(int i = 0; i < d_N; ++i)
	{
		std::vector<int> tmp;
		d_edges.push_back(tmp);
	}
}

void Digraph::addEdge(int w, int v)
{
	if(w < 0 || w >= d_N || v < 0 || v >= d_N)
	{
		return;
	}
	d_edges[w].push_back(v);
}

void Digraph::search(std::vector<int>& pc, int source)
{
	dfs(source);
	for(size_t i = 0; i < d_N; ++i)
	{
		if(d_mark[i])
		{
			pc.push_back(i);
			d_mark[i] = false; //reset to default
		}
	}
}

void Digraph::search(std::vector<int>& pc, const std::vector<int>& match)
{
	for(size_t i = 0; i < match.size(); ++i)
	{
		dfs(match[i]);
	}
	for(size_t i = 0; i < d_N; ++i)
	{
		if(d_mark[i])
		{
			pc.push_back(i);
			d_mark[i] = false; //reset to default
		}
	}
}

void Digraph::dfs(int source)
{
	if(!d_mark[source])
	{
		d_mark[source] = true;
		std::vector<int> edges;
		getEdges(edges, source);
		for(size_t j = 0; j < edges.size(); ++j)
		{
			dfs(edges[j]);
		}
	}
}

void Digraph::getEdges(std::vector<int>& edges, int w)
{
	if(w < 0 || w >= d_N) return;
	edges = d_edges[w];
}

void Digraph::print() const
{
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << i << ": ";
		for(size_t j = 0; j < d_edges[i].size(); ++j)
		{
			std::cout << d_edges[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
