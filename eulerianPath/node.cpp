#include "node.h"
#include <iostream>

Node::Node(int v)
{
	x = v;
	prev = 0;
	next = 0;
}

void Node::addEdge(int v)
{
	Node* n = new Node(v);
	Node* p = this;
	while( p->next != 0)
	{
		p = p->next;
	}
	p->next = new Node(v);
	p->next->prev = p;
}

Node::~Node()
{	
}
