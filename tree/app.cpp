#include "bst.h"
#include "red_black_tree.h"
#include <string>
#include <iostream>

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
	rbt.put(8, 64);
	rbt.put(4, 16);
	rbt.put(10, 100);
	rbt.put(2, 4);
	rbt.put(6, 36);
	rbt.put(9, 49);
	rbt.put(11, 121);
	rbt.put(1, 1);
	rbt.put(3, 9);
	rbt.put(5, 25);
	rbt.put(7, 49);
	testing(&rbt);
}

int main()
{
	testBSTString();
	testRBTString();
	return 0;
}
