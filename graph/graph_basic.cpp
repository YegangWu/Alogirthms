#include "graph_basic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph()
{
	N = 0;
	std::cout << "Empty graph!" << std::endl;
}

Graph::Graph(const std::string& filename)
{
	N = 0;
	std::ifstream infile(filename);
	std::string line;
	if( !std::getline(infile, line) )
	{
		return;
	}
	std::stringstream ss(line);
	int n;
	if( !(ss >> n) )
	{
		return;
	}	
	N = n;
	//add empty list for each vertex
	for(int i = 0; i < N; ++i)
	{
		std::vector<int> tmp;
		eglist.push_back(tmp);
	}

	while(std::getline(infile, line))
	{
		std::stringstream ss(line);
		int w, v;
		if( !(ss >> w >> v) )
		{
			break;
		}
		addEdge(w, v);
	}	
}

void Graph::addEdge(int w, int v)
{
	if( !edgeInGraph(w) || !edgeInGraph(v) )
	{
		std::cerr << "Vertices are not in the graph!" << std::endl;
	}
	if( std::find(eglist[w].begin(), eglist[w].end(), v) == eglist[w].end() )
	{
		eglist[w].push_back(v);
	}
}

bool Graph::edgeInGraph(int v) const
{
	return v >= 0 && v < eglist.size();
}

bool Graph::edgeFrom(std::vector<int>& edge, int v) const
{
	if( !edgeInGraph(v) )
	{
		std::cerr << "Vertex " << v << " is not in the graph!" << std::endl;
		return false;
	}
	edge = eglist[v];
	return true;
}

int Graph::size() const
{
	return N;
}

void Graph::print()
{
	std::cout << "There are " << N << " vertices" << std::endl;
	for(size_t i = 0; i < eglist.size(); ++i)
	{
		std::cout << i << ": ";
		for(size_t j = 0; j < eglist[i].size(); ++j)
		{
			std::cout << eglist[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
