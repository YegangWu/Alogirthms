#include "eucycle.h"
#include <stdexcept>
#include <iostream>

namespace
{
	const std::string STUCK_WITH_NODE = "Stuck with node without exist edges.";
	const std::string COULD_NOT_COMBINE = "Could not combine two cycles.";
}

EuCycle::EuCycle(Graph& g)
{
	d_N = g.size();
	d_visitedCycle = 0;
	d_currentPath = 0;
}

void EuCycle::findCycle(Graph& g, int v)
{
	d_currentPath = new Node(v);
	d_origin = v;
	dfs(g, d_origin);

	while(findNewOrigin(g))
	{
		d_currentPath = new Node(d_origin);
		dfs(g, d_origin);
	}	
	printCurrentCycle();
}

void EuCycle::dfs(Graph& g, int v)
{
	Node* edgeHead = g.edgeFrom(v);
	throwOnNull(edgeHead, STUCK_WITH_NODE);
	
	int w = edgeHead->x;
	if(w != d_origin)
	{
		while(edgeHead->next != 0)
		{
			std::cout << "skip vertex " << edgeHead->x << std::endl;
			edgeHead = edgeHead->next;
			w = edgeHead->x;
			if( w == d_origin )
			{
				break;
			}
		}
	}
	if( w == d_origin )
	{
		std::cout << "find origin " << d_origin << std::endl;
		d_currentPath->addEdge(w);
		g.deleteEdge(v, w);
		g.deleteEdge(w, v);
		std::cout << "start combining cycles" << std::endl;
		combineVisitedCycles();
		return;
	}
	std::cout << "Find vertex " << w << std::endl;
	d_currentPath->addEdge(w);
	g.deleteEdge(v, w);
	g.deleteEdge(w, v);
	std::cout << "dfs on vertex " << w << std::endl;
	g.print();
	dfs(g, w);
}

void EuCycle::combineVisitedCycles()
{
	Node* p = d_visitedCycle;
	if(p == 0)
	{
		d_visitedCycle = d_currentPath;
	}
	else
	{
		while(p->x != d_origin)
		{
			p = p->next;
		}
		throwOnNull(p, COULD_NOT_COMBINE);	

		Node* q = p->next;
		if(p->prev != 0)
		{
			p->prev->next = d_currentPath;
		}
		else
		{
			d_visitedCycle = d_currentPath;
		}
		delete p;
		p = d_currentPath;
		while(p->next != 0)
		{
			p = p->next;
		}
		p->next = q;
		q->prev = p;
	}
	d_currentPath = 0;
}

void EuCycle::throwOnNull(Node* p, const std::string& errorMsg)
{
	if(p == 0)
	{
		throw std::runtime_error( errorMsg );
	}
}

bool EuCycle::findNewOrigin(Graph& g)
{
	Node* p = d_visitedCycle;
	while(p != 0)
	{
		int w = p->x;
		if(g.edgeFrom(w) != 0)
		{
			d_origin = w;
			return true;
		}
		p = p->next;
	}
	return false;
}

void EuCycle::test_findFirstCycle(Graph& g, int v)
{
	d_currentPath = new Node(v);
	d_origin = v;
	std::cout << "start dfs" << std::endl;
	dfs(g, d_origin);
	printCurrentCycle();	
	g.print();
	if(findNewOrigin(g))
	{
		std::cout << "new origin is " << d_origin << std::endl;
	}
	else
	{
		std::cout << "Could not find new origin" << std::endl;
	}
	d_currentPath = new Node(d_origin);
	dfs(g, d_origin);
	printCurrentCycle();	
	if(findNewOrigin(g))
	{
		std::cout << "new origin is " << d_origin << std::endl;
	}
	else
	{
		std::cout << "Could not find new origin" << std::endl;
	}
}

void EuCycle::printCurrentCycle()
{
	Node* p = d_visitedCycle;
	while(p)
	{
		std::cout << p->x << "->";
		p = p->next;
	}
	std::cout << std::endl;
}
