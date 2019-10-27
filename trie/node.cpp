#include "node.h"
#include <iostream>

Node::Node():value(user::INVALID)
{
	for(int i = 0; i < R; ++i)
	{
		next[i] = NULL;
	}
}

Node::Node(int value): value(value)
{
	for(int i = 0; i < R; ++i)
	{
		next[i] = NULL;
	}
}

bool Node::empty()
{
	for(int i = 0; i < R; ++i)
	{
		if(next[i])
		{
			return false;
		}
	}
	return true;
}
