#include "bst.h"
#include "red_black_tree.h"
#include <string>
#include <iostream>

void testFindCeilings(BST<std::string>* bst, const std::string& str)
{	
	Node<std::string>* parent = NULL;
	Node<std::string>* t = bst->successor(str, &parent);
	std::cout << "The successor of " << str << " is " << (t == NULL ? " (no exist)." : t->key) 
					<< " It's parent is " << (parent == NULL ? "(no exist)." : parent->key) << std::endl;

}

void testing(BST<std::string>* bst)
{
	std::cout << "air's number is " << bst->get("air")->v << std::endl;
	std::cout << "wood's number is " << bst->get("wood")->v << std::endl;
	std::cout << "fog's number is " << bst->get("fog")->v << std::endl;

	std::cout << "Contains sun? " << (bst->contains("sun") ? "Yes" : "No") << std::endl;
	std::cout << "Contains mars? " << (bst->contains("mars") ? "Yes" : "No") << std::endl;
	std::cout << "Contains jupiter? " << (bst->contains("jupiter")? "Yes" : "No") << std::endl;

	std::vector<Node<std::string>* > list;
	list = bst->inorder();
	std::vector<Node<std::string>* >::const_iterator iter = list.begin();
	for(; iter != list.end(); ++iter)
	{
		std::cout << "(" << (*iter)->key << ": " << (*iter)->v << "<" << (*iter)->rank << ">), ";
	}
	std::cout << std::endl;

	std::string str = "fire";
	Node<std::string>* t = bst->floor(str);
	std::cout << "The floor of " << str << " is " << (t == NULL ? " (no exist)" : t->key) << std::endl;
	
	testFindCeilings(bst, "fire");
	testFindCeilings(bst, "cloud");
	testFindCeilings(bst, "sun");
	testFindCeilings(bst, "air");
	testFindCeilings(bst, "dust");
	testFindCeilings(bst, "metal");
	testFindCeilings(bst, "water");
	testFindCeilings(bst, "fog");
	testFindCeilings(bst, "moon");
	testFindCeilings(bst, "wood");

}


void testBSTString()
{
	BST<std::string> bst;
	bst.put("air", 1);
	bst.put("cloud", 9);
	bst.put("dust", 8);
	bst.put("fire", 5);
	bst.put("fog", 7);
	bst.put("metal", 4);
	bst.put("moon", 10);
	bst.put("sun", 6);
	bst.put("water", 3);
	bst.put("wood", 2);
	
	testing(&bst);
}

void testRBTString()
{
	RedBlackTree<std::string> rbt;
	rbt.put("air", 1);
	rbt.put("cloud", 9);
	rbt.put("dust", 8);
	rbt.put("fire", 5);
	//rbt.remove("cloud");
	rbt.put("fog", 7);
	rbt.put("metal", 4);
	rbt.put("moon", 10);
	rbt.put("sun", 6);
	//rbt.remove("fog");
	rbt.put("water", 3);
	rbt.put("wood", 2);
	
	testing(&rbt);
}

int main()
{
	testBSTString();
	testRBTString();
	return 0;
}
