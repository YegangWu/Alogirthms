#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

const int R = 26;
namespace user
{
	const int INVALID = -99999;
}

struct Node
{
	Node();
	Node(int value);
	bool empty();

	int value;
	Node* next[R];
};

#endif
