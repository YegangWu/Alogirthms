#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

struct Node
{
	int x;
	Node* prev;
	Node* next;

	Node(int v);
	~Node();
	void addEdge(int v);
};

#endif
