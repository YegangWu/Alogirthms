#include "bipartite.h"
#include <iostream>

BP::BP(const Graph& g)
{
	d_isBipartite = true;
	d_N = g.size();
	for(int i = 0; i < d_N; ++i)
	{
		d_color.push_back('u');
	}
	for(int i = 0; i < d_N; ++i)
	{
		if(d_color[i] == 'u')
		{
			//if( !dfs(g, i, 'r') )
			if( !bfs(g, i, 'r') )
			{
				d_isBipartite = false;
				return;	
			}
		}
	}
}

bool BP::dfs(const Graph& g, int v, char c)
{
	char reverse = getReverse(c);
	if(d_color[v] == reverse)
	{
		return false;
	}
	else if(d_color[v] == c)
	{
		return true;
	}

	d_color[v] = c;
	std::vector<int> edges;
	g.edgeFrom(edges, v);
	for(std::vector<int>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
	{
		int w = *iter;
		if(d_color[w] == reverse)
		{
			continue;
		}
		else if( d_color[w] == c || !dfs(g, w, reverse) )
		{
			return false;
		}
	}
	return true;
}

char BP::getReverse(char c)
{
	return c == 'r' ? 'b' : 'r';
}

bool BP::bfs(const Graph& g, int v, char c)
{
	d_color[v] = c;
	q.push(v);
	while( !q.empty() )
	{	
		int w = q.front();
		q.pop();
	    char currentColor = d_color[w];
		char reverse = getReverse(currentColor);
		std::vector<int> edges;
		g.edgeFrom(edges, w);
		for(std::vector<int>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			int x = *iter;
			if( d_color[x] == currentColor )
			{
				return false;
			}
			else if( d_color[x] == reverse )
			{
				continue;
			}
			d_color[x] = reverse;
			q.push(x);	
		}
	}
	return true;
}

void BP::report()
{
	std::cout << "This graph is ";
	if( ! d_isBipartite )
	{
		std::cout << "not ";
	}
	std::cout << "a bipartite graph." << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << d_color[i] << ", ";
	}
	std::cout << std::endl;
}
