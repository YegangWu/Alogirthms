#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

class Node
{
	public:
		char d_c;
		int d_freq;
		Node* left;
		Node* right;
		Node(char c, int freq, Node* left, Node* right): d_c(c), d_freq(freq), left(left), right(right) {}
		friend struct greater;
};

struct greater
{
	bool operator()(const Node* lhs, const Node* rhs)
	{
		return lhs->d_freq > rhs->d_freq;
	}
};

#endif
