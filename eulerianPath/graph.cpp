#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph(const std::string& file)
{
	std::ifstream infile(file);
	std::string line;
	std::getline(infile, line);
	std::stringstream ss(line);
	ss >> d_N;
	std::cout << "read " << d_N << std::endl;
	Node* head = 0;
	for(int i = 0; i < d_N; ++i)
	{
		d_edgeList.push_back(head);
	}
	while(std::getline(infile, line))
	{
		int v, w;
		std::stringstream ss(line);
		ss >> v >> w;
		if(d_edgeList[v] == 0)
		{
			d_edgeList[v] = new Node(w);
		}
		else
		{
			d_edgeList[v]->addEdge(w);
		}
	}
}

int Graph::size()
{
	return d_N;
}

Node* Graph::edgeFrom(int v)
{
	return d_edgeList[v];
}

void Graph::deleteEdge(int v, int w)
{
	std::cout << "delete edge (" << v << ", " << w << ")" << std::endl;
	Node* edgeHead = d_edgeList[v];
	if(edgeHead == 0) //no edges from v
	{
		return;
	}
	while(edgeHead->x != w)
	{
		edgeHead = edgeHead->next;
	}
	if(edgeHead == 0) //edge v->w not found
	{
		return;
	}
	if(edgeHead->prev != 0)
	{
		std::cout << "edgeHead prev is not null" << std::endl;
		edgeHead->prev->next = edgeHead->next;
		if(edgeHead->next)
		{
			edgeHead->next->prev = edgeHead->prev;
		}
	}
	else
	{
		std::cout << "edgeHead prev is null" << std::endl;
		d_edgeList[v] = edgeHead->next;
		if(d_edgeList[v])
		{
			d_edgeList[v]->prev = 0;
		}
	}
	delete edgeHead;
}

void Graph::print()
{
	std::cout << "There are " << d_N << " nodes." << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		Node* p = d_edgeList[i];
		while(p)
		{
			std::cout << p->x << ", ";
			p = p->next;
		}
		std::cout << std::endl;
	}
}
