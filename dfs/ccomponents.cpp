#include "ccomponents.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

CC::CC(const Graph& g)
{
	d_N = g.size();
	for(int i = 0; i < d_N; ++i)
	{
		marked.push_back(false);
		idList.push_back(i);
	}
	d_count = 0;
	for(int i = 0; i < d_N; ++i)
	{
		if(!marked[i])
		{
			dfs(g, i, d_count);
			d_count++;
		};
	}
	std::srand(std::time(0));
}

void CC::dfs(const Graph& g, int v, int clusterId)
{
	if(!marked[v])
	{
		marked[v] = true;
		idList[v] = clusterId;

		std::vector<int> edges;
		g.edgeFrom(edges, v);
		for(std::vector<int>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
		{
			int w = *iter;
			if(!marked[w])
			{
				marked[w] = true;
				idList[w] = clusterId;
				dfs(g, w, clusterId);
			}
		}
	}	
}

bool CC::connected(int v, int w)
{
	if(v < 0 || v >= d_N || w < 0 || w >= d_N) 
	{
		return false;
	}
	return idList[v] == idList[w];
}

int CC::count()
{
	return d_count;
}

int CC::id(int v)
{
	return idList[v];
}

void CC::printInfo()
{
	std::cout << "There are " << d_count << " clusters" << std::endl;
	for(int i = 0; i < 5; ++i)
	{
		int v = std::rand()%d_N;
		int w = std::rand()%d_N;
		std::cout << "Vertex " << v << " and vertex " << w;
		if(connected(v, w))
		{
			std::cout << " are connected." << std::endl;
		}
		else
		{
			std::cout << " are not connected." << std::endl;
		}
	}
}
