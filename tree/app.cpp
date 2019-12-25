#include "bst.h"
#include "red_black_tree.h"
#include <string>
#include <iostream>
#include <random>

void testFindSuccessor(BST<int>* bst, int n)
{	
	std::stack<Node<int>* > pathTo;
	Node<int>* t = bst->findSuccessor(n, pathTo);
	std::cout << "The successor of " << n << " is " << (t == NULL ? " (no exist)." : std::to_string(t->key)) << ". "; 
	std::cout << "The path to its successor is: " << std::endl;
	while(!pathTo.empty())	
	{
		std::cout << pathTo.top()->key << ", ";
		pathTo.pop();
	}
	std::cout << std::endl;
}

void testing(BST<int>* bst)
{
	testFindSuccessor(bst, 1);
	testFindSuccessor(bst, 2);
	testFindSuccessor(bst, 3);
	testFindSuccessor(bst, 4);
	testFindSuccessor(bst, 5);
	testFindSuccessor(bst, 6);
	testFindSuccessor(bst, 7);
	testFindSuccessor(bst, 8);
	testFindSuccessor(bst, 9);
	testFindSuccessor(bst, 10);

	bst->describeGraph();
	bst->remove(3);
	bst->describeGraph();
}


void testBSTString()
{
	BST<int> bst;
	bst.put(4, 16);
	bst.put(2, 4);
	bst.put(6, 36);
	bst.put(1, 1);
	bst.put(3, 9);
	bst.put(5, 25);
	bst.put(7, 49);
	
	testing(&bst);
}

void testRBTString()
{
	RedBlackTree<int> rbt;
	/*
	rbt.put(12, 144);
	rbt.put(8, 64);
	rbt.put(14, 196);
	rbt.put(6, 36);
	rbt.put(10, 100);
	rbt.put(13, 169);
	rbt.put(16, 256);
	rbt.put(2, 4);
	rbt.put(7, 49);
	rbt.put(9, 81);
	rbt.put(11, 121);
	rbt.put(15, 225);
	rbt.put(1, 1);
	rbt.put(4, 8);
	rbt.describeGraph();
	rbt.remove(8);
	rbt.describeGraph();
	*/

	
	std::vector<int> nodes;
	for(int i = 1; i <= 256; ++i) {
		nodes.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(nodes.begin(), nodes.end(), g);

	for(size_t i = 0; i < nodes.size(); ++i) {
		int node = nodes[i];
		std::cout << "addinginging " << node << std::endl;
		rbt.put(node, node*node);
	}
	rbt.describeGraph();

	std::shuffle(nodes.begin(), nodes.end(), g);
	for(size_t i = 0; i < nodes.size(); ++i) {
		int node = nodes[i];
		rbt.remove(node);
		rbt.describeGraph();
	}
}

int main()
{
	testRBTString();
	return 0;
}
