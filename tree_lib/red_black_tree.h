#ifndef INCLUDE_RED_BLACK_TREE_H
#define INCLUDE_RED_BLACK_TREE_H

#include "bst.h"
#include <iostream>
#include <cassert>

template<class T>
class RedBlackTree: public BST<T>
{
	public:
		RedBlackTree();
		virtual void put(T key, int v);	
		virtual void remove(T key);	
		Node<T>* findSuccessor(T key, std::stack<Node<T>* >& pathTo);
		Node<T>* rightRotate(Node<T>* root);
		Node<T>* leftRotate(Node<T>* root);
		void reverseColor(Node<T>* root);
	private:
		Node<T>* put(Node<T>* root, T key, int v, int rank);

		Node<T>* get(T key, Node<T>** parent);
		Node<T>* successor(Node<T>* root, T key, std::stack<Node<T>* >& pathTo);
		void findPath(T key, std::stack<Node<T>* >& pathTo);
		void findPath(Node<T>* root, T key, std::stack<Node<T>* >& pathTo);
		void assign(Node<T>* dest, Node<T>* source);
		Node<T>* findSibling(Node<T>* parent, Node<T>* t);
		Node<T>* updateGrandParent(Node<T>* parent, Node<T>* sibling, std::stack<Node<T>* >& pathTo);
		void remove(Node<T>* successor, std::stack<Node<T>* >& pathTo);
		void rebalance(Node<T>* t, Node<T>* parent, std::stack<Node<T>* >& pathTo);
};

template<class T>
RedBlackTree<T>::RedBlackTree(): BST<T>()
{
}

template<class T>
void RedBlackTree<T>::put(T key, int v)
{
	BST<T>::d_root = put(BST<T>::d_root, key, v, 0);
}

template<class T>
Node<T>* RedBlackTree<T>::put(Node<T>* root, T key, int v, int rank)
{
	if(root == NULL) {
		std::cout << "insert " << key << std::endl;
		return new Node<T>(key, v, rank);
	}
	if(key < root->key)
	{
		root->left = put(root->left, key, v, rank);
		root->rank += 1;
	}
	else if(key > root->key)
	{
		rank = root->rank + 1;
		root->right = put(root->right, key, v, rank);
	}
	else {
		root->v = v;
	}
	if(isRed<T>(root->right) && !isRed<T>(root->left)) {
		root = leftRotate(root);
	}
	if(isRed<T>(root->left) && isRed<T>(root->left->left)) {
		root = rightRotate(root);
	}
	if(isRed<T>(root->left) && isRed<T>(root->right)) {
		reverseColor(root);
	}	
	return root;
}

template<class T>
Node<T>* RedBlackTree<T>::rightRotate(Node<T>* root)
{
	std::cout << "right rotate " << root->key << std::endl;
	Node<T>* t = root->left;
	root->left = t->right;
	t->right = root;
	t->color = root->color;
	root->color = RED;
	return t;
}

template<class T>
Node<T>* RedBlackTree<T>::leftRotate(Node<T>* root)
{
	std::cout << "left rotate " << root->key << std::endl;
	Node<T>* t = root->right;
	root->right = t->left;
	t->left = root;
	t->color = root->color;
	root->color = RED;
	return t;
}

template<class T>
void RedBlackTree<T>::reverseColor(Node<T>* root)
{
	std::cout << "recolor " << root->key << std::endl;
	root->left->color = BLACK;
	root->right->color = BLACK;
	root->color = RED;
}

template<class T>
Node<T>* RedBlackTree<T>::get(T key, Node<T>** parent)
{
	std::cout << "In red black tree, get " << key << std::endl;
	Node<T>* t = BST<T>::d_root;
	*parent = NULL;
	while(t != NULL)
	{
		if(key == t->key) {
			return t;
		}
		else {
			*parent = t;
			if(key < t->key) {
				t = t->left;
			}
			else { 
				t = t->right;
			}
		}
	}
	return t;
}

template<class T>
Node<T>* RedBlackTree<T>::findSuccessor(T key, std::stack<Node<T>* >& pathTo)
{
	return successor(BST<T>::d_root, key, pathTo);
}

template<class T>
Node<T>* RedBlackTree<T>::successor(Node<T>* root, T key, std::stack<Node<T>* >& pathTo)
{
	if(root == NULL) {
		return NULL;
	}
	pathTo.push(root);
	if(key >= root->key) {
		Node<T>* t = successor(root->right, key, pathTo);
		if(t == NULL) {
			pathTo.pop();
		}
		return t;
	}
	else {
		Node<T>* t = successor(root->left, key, pathTo);
		if(t == NULL) {
			return root;
		}
		return t;
	}
}

template<class T>
void RedBlackTree<T>::findPath(T key, std::stack<Node<T>* >& pathTo)
{
	findPath(BST<T>::d_root, key, pathTo);
}

template<class T>
void RedBlackTree<T>::findPath(Node<T>* root, T key, std::stack<Node<T>* >& pathTo)
{
	if(root == NULL) {
		return;
	}
	if(key == root->key) {
		return;
	}
	std::cout << "In findPath, push " << root->key << std::endl;
	pathTo.push(root);
	if(key < root->key) {
		findPath(root->left, key, pathTo);
	}
	else {
		findPath(root->right, key,pathTo);
	}
}

template<class T>
void RedBlackTree<T>::assign(Node<T>* dest, Node<T>* source)
{
	dest->key = source->key;
	dest->v = source->v;
}

template<class T>
Node<T>* RedBlackTree<T>::findSibling(Node<T>* parent, Node<T>* t)
{
	if(t == parent->left) {
		return parent->right;
	}
	return parent->left;
}

template<class T>
Node<T>* RedBlackTree<T>::updateGrandParent(Node<T>* parent, Node<T>* sibling, std::stack<Node<T>* >& pathTo) {
	if(pathTo.empty()) {
		std::cout << "sibling " << sibling->key << " will be the root" << std::endl;
		BST<T>::d_root = sibling;
		return NULL;
	}

	Node<T>* grandparent = pathTo.top();
	pathTo.pop();
	if(parent == grandparent->left) {
		grandparent->left = sibling;
	}
	else {
		grandparent->right = sibling;
	}
	sibling->color = parent->color;
	return grandparent;
}

template<class T>
void RedBlackTree<T>::remove(T key)
{
	Node<T>* t;
	Node<T>* parent;
	t = get(key, &parent);
	if(t == NULL) {
		return;
	}
		
	if(t->left == NULL && t->right == NULL) {
		if (t == BST<T>::d_root) {
			delete t;
			BST<T>::d_root = NULL;
			return;
		}

		if(t->color == RED) {
			//test case: {2, 1, 4, 3}; delete 3;
			//pass test
			std::cout << "In simple remove, case 1.1" << std::endl;
			parent->left = NULL;
			delete t;
			return;
		}
		else {
			//pass test
			//test case: {2, 1, 4, 3}; delete 1;
			std::cout << "In simple remove, case 1.2" << std::endl;
			std::cout << "find path for " << key << std::endl;
			std::stack<Node<T>* > pathTo;
			findPath(key, pathTo);
			remove(t, pathTo);
			return;
		}
	}
	else if (t->left != NULL && t->left->color == RED && t->right == NULL) {
		if(t == BST<T>::d_root) {
			assert(parent == NULL);
			BST<T>::d_root = t->left;
			delete t;
			return;
		}
		if(t == parent->left) {
			//pass test
			//test case: {3, 2, 5, 1, 4}; delete 2;
			std::cout << "In simple remove, case 2.1" << std::endl;
			parent->left = t->left;
			parent->left->color = BLACK;
		}
		else {
			//pass test
			//test case: {2, 1, 4, 3}; delete 4;
			std::cout << "In simple remove, case 2.2" << std::endl;
			parent->right = t->left;
			parent->right->color = BLACK; 
		}
		delete t;
		return;
	}

	std::stack<Node<T>* > pathTo;
	Node<T>* successor = findSuccessor(key, pathTo);
	std::cout << "successor is " << successor->key << std::endl;

	assert(successor != NULL);
	/*
	if(successor == NULL)
	{
		//t is right child of its parent, why?
		if(t->left != NULL) {
			t->left->color = t->color;
			parent->right = t->left;
		}
		else {
			parent->right = NULL;
		}
		delete t;
		return;
	}
	*/
	
	//replace t with its successor
	assign(t, successor);
	pathTo.pop();
	remove(successor, pathTo);
}

template<class T>
void RedBlackTree<T>::remove(Node<T>* successor, std::stack<Node<T>* >& pathTo)
{	
	//case 1, it has no sibling
	//       |            |
	//	     o     or     x
	//	 (r)/            /
	//     x            o
	std::cout << "In remove for successor (" << successor->key << ", " << successor->color << ")" << std::endl;
	if(successor->color == RED) {
		std::cout << "In remove, case 1.0" << std::endl;
		//pass test
		//test case: {2, 1, 4, 3}; delete 2;
		assert(successor->left == NULL && successor->right == NULL);
		assert(!pathTo.empty());
		Node<T>* parent = pathTo.top();
		pathTo.pop();
		parent->left = NULL;
		delete successor;
		return;
	}
	assert(successor->left == NULL);
	//meaning the second case in above graph doesn't exist, why?
	/*
	if(successor->left != NULL) {
		assert(successor->left->color == RED);
		assert(successor->left->right == NULL);
		if(pathTo.empty()) {
			std::cout << "In remove, case 1.1" << std::endl;
			BST<T>::d_root = successor->left;
		}
		else {
			std::cout << "In remove, case 1.2" << std::endl;
			Node<T>* parent = pathTo.top();
			pathTo.pop();
			successor->left->color = successor->color;
			if(parent->left == successor) {
				std::cout << "In remove, case 1.2.1" << std::endl;
				parent->left = successor->left;
			}
			else {
				std::cout << "In remove, case 1.2.2" << std::endl;
				parent->right = successor->left;
			}	
		}	
		delete successor;
		return;
	}*/

	Node<T>* parent = pathTo.top();
	pathTo.pop();
	Node<T>* sibling = findSibling(parent, successor);

	//case 2, its sibling has one child
	//        |                     |
	// 		  o					    o
	//    (b)/ \(b)    or       (b)/ \(b)
	//      o   x                 x   o
	//  (r)/                         /(r)
	//    o                         o
	std::cout << "sibling is " << sibling->key << std::endl;
	if(sibling->left != NULL && sibling->right == NULL) {
		std::cout << "In remove, case 2" << std::endl;
		assert(sibling->left->color == RED);
		if(sibling == parent->left) {
			//pass test
			//test case: {5, 3, 7, 2, 4, 1}; delete 4;
			std::cout << "In remove, case 2.1" << std::endl;
			sibling->right = parent;
			sibling->left->color = BLACK;
			parent->left = NULL;
			parent->right = NULL;
			updateGrandParent(parent, sibling, pathTo);
			sibling->right->color = BLACK;
		}
		else {
			//pass test
			//test case: {5, 2, 6, 1, 4, 3}; delete 1;
			std::cout << "In remove, case 2.2" << std::endl;
			Node<T>* node = sibling->left;
			node->left = parent;
			node->right = sibling;
			sibling->left = NULL;
			parent->left = NULL;
			parent->right = NULL;
			updateGrandParent(parent, node, pathTo);
			node->left->color = BLACK;
		}
		delete successor;
		return;
	}		

	//case 3, its sibling has two children. The sibling must be the left children whose color is red. Why?
	//       |                  case 3.1:   |                   case 3.2    |
	//	     o                              o                               o
	//   (r)/ \(b)                      (r)/ \(b)                       (r)/ \(b)
	//     o   x                          o   x                           o   x
	// (b)/ \(b)                      (b)/ \(b)                       (b)/ \(b)
	//   2   3                          2   o                           2   3 
	//                                     /(r)
    //                                    3
	if(sibling->left != NULL && sibling->right != NULL) {
		std::cout << "In remove, case 3" << std::endl;
		assert(sibling->color == RED);
		assert(parent == BST<T>::d_root || parent->color == BLACK);
		if(sibling->right->left != NULL) {  //case 3.1
			//test case: {7, 5, 9, 2, 6, 8, 10, 1, 4, 3}; delete 6;
			//pass test
			std::cout << "In remove, case 3.1" << std::endl;
			assert(sibling->right->left->color == RED);
			Node<T>* node = sibling->right;
			sibling->right = node->left;	
			sibling->right->color = BLACK;
			node->left = sibling;
			node->right = parent;
			parent->left = NULL;
			parent->right = NULL;
			updateGrandParent(parent, node, pathTo);
			parent->color = BLACK;
		}
		else { //case 3.2
			//pass test
			//test case: {7, 5, 9, 2, 6, 8, 10, 1, 4}; delete 6;
			std::cout << "In remove, case 3.2" << std::endl;
			parent->left = sibling->right;
			parent->left->color = RED;
			parent->right = NULL;
			sibling->right = parent;
			updateGrandParent(parent, sibling, pathTo);
			parent->color = BLACK;
		}
		delete successor;
		return;
	}

	//case 4, its sibling has no children.
	//   (b)|            (b)  |              (r)|            (r)|          
	//      o                 o                 o               o
	//  (b)/ \(b)   or    (b)/ \(b)   or    (b)/ \(b)   or  (b)/ \(b)
    //    x   o             o   x             x   o           o   x
    //
	if(sibling->left == NULL && sibling->right == NULL) {
		assert(sibling->color == BLACK);
		std::cout << "In reomve, case 4" << std::endl;
		std::cout << "successor is (" << successor->key << ", " << successor->color << "), sibling is (" << sibling->key << ", " << sibling->color << "), parent is (" << parent->key << ", " << parent->color << ")" << std::endl;
		if(sibling == parent->left) {
			//pass test
			//test case: {4, 2, 6, 1, 3, 5, 7}; delete 7;
			std::cout << "In reomve, case 4.1" << std::endl;
			sibling->color = RED;
			parent->right = NULL;
			delete successor;

			if(parent->color == RED) {
				//pass
				//test case: {6, 4, 7, 3, 5}; delete 5;
				std::cout << "In reomve, case 4.1.1" << std::endl;
				parent->color = BLACK;
				return;
			}

			if(pathTo.empty()) {
				//pass
				//test case: {2, 1, 3}; delete 3;
				std::cout << "In reomve, case 4.1.2" << std::endl;
				return;
			}
			Node<T>* grandparent = pathTo.top();
			pathTo.pop();
			std::cout << "parent is " << parent->key << ", grandparent is " << grandparent->key << std::endl;
			rebalance(parent, grandparent, pathTo);
			std::cout << "rebalance returns, root is " << BST<T>::d_root->key << std::endl;
			return;
		}
		else {
			//pass test
			//test case: {2, 1, 3}; delete 3;
			std::cout << "In reomve, case 4.2" << std::endl;
			sibling->left = parent;
			parent->left = NULL;
			parent->right = NULL;
			delete successor;

			Node<T>* grandparent = updateGrandParent(parent, sibling, pathTo);
			if(parent->color == RED) {
				//pass test
				//test case: {6, 4, 7, 3, 5}; delete 3;
				std::cout << "In reomve, case 4.2.1" << std::endl;
				sibling->color = BLACK;
				return;
			}
			else {
				std::cout << "In reomve, case 4.2.2" << std::endl;
				sibling->color = BLACK;
				sibling->left->color = RED;
				rebalance(sibling, grandparent, pathTo);
				return;
			}
		}
	}
	assert(false);	
}

template<class T>
void RedBlackTree<T>::rebalance(Node<T>* t, Node<T>* parent, std::stack<Node<T>* >& pathTo)
{
	if(parent == NULL) {
		return;
	}

	Node<T>* sibling = findSibling(parent, t);
	std::cout << "In rebalance, t is (" << t->key << ", " << t->color << "), sibling is (" << sibling->key << ", " << sibling->color << "), parent is (" << parent->key << ", " << parent->color << ")" << std::endl;
	if(t == parent->right) {
		std::cout << "rebalance, case 1" << std::endl;
		assert(sibling->left != NULL);
		assert(sibling->right != NULL);
		if(sibling->color == BLACK) {
			std::cout << "rebalance, case 1.1" << std::endl;
			if(sibling->left->color == BLACK) {
				std::cout << "rebalance, case 1.1.1" << std::endl;
				sibling->color = RED;
				if(parent->color == RED) {
					//pass test
					//test case: {4, 2, 6, 1, 3, 5, 7}; delete 7;
					std::cout << "rebalance, case 1.1.1.1" << std::endl;
					parent->color = BLACK;
				}
				else {
					//pass test
					//test case:{8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15}; delete 13;
					std::cout << "rebalance, case 1.1.1.2" << std::endl;
					//propogate...	
					if(parent == BST<T>::d_root) {
						return;
					}
					assert(!pathTo.empty());
					Node<T>* grandParent = pathTo.top();
					pathTo.pop();
					rebalance(parent, grandParent, pathTo);
				}
			}
			else {
				//pass test
				//test case:{6, 4, 8, 2, 5, 7, 9, 1, 3}; delete 9;
				std::cout << "rebalance, case 1.1.2" << std::endl;
				parent->left = sibling->right;
				sibling->right = parent;
				sibling->left->color = BLACK;
				updateGrandParent(parent, sibling, pathTo);
				parent->color = BLACK;
			}
		}
		else {
			std::cout << "rebalance, case 1.2" << std::endl;
			assert(sibling->left->color = BLACK);
			if(sibling->right->left->color == BLACK) {
				//pass test
				//test case: {8, 4, 10, 2, 6, 9, 11, 1, 3, 5, 7}; delete 11;
				std::cout << "rebalance, case 1.2.1" << std::endl;
				assert(parent == BST<T>::d_root || parent->color == BLACK);
				parent->left = sibling->right;
				parent->left->color = RED;
				sibling->right = parent;
				sibling->right->color = BLACK;
				updateGrandParent(parent, sibling, pathTo);
			}
			else {
				//pass test
				//test case: {10, 4, 12, 2, 8, 11, 13, 1, 3, 6, 9, 5, 7}; delete 11;
				std::cout << "rebalance, case 1.2.2" << std::endl;
				assert(parent == BST<T>::d_root || parent->color == BLACK);
				Node<T>* node = sibling->right;
				parent->left = node->right;
				sibling->right = node->left;
				sibling->right->color = BLACK;
				node->left = sibling;
				node->right = parent;
				node->right->color = BLACK;
				updateGrandParent(parent, node, pathTo);	
			}
		}
	}
	else {
		std::cout << "rebalance, case 2" << std::endl;
		if(sibling->left->color == RED) {
			//pass test
			//test case: {4, 2, 8, 1, 3, 6, 9, 5, 7}; delete 1;
			std::cout << "rebalance, case 2.1" << std::endl;
			assert(sibling->left->left != NULL);
			assert(sibling->left->right != NULL);
			Node<T>* node = sibling->left;
			parent->right = node->left;
			sibling->left = node->right;
			node->left = parent;
			node->right = sibling;
			std::cout << "node is (" << node->key << ", " << node->color << "), parent is (" << parent->key << ", " << parent->color << ")" << std::endl;
			updateGrandParent(parent, node, pathTo);
			parent->color = BLACK;
			return;
		}
		else {
			std::cout << "rebalance, case 2.2" << std::endl;
			sibling->color = RED;
			parent->right = sibling->left;
			sibling->left = parent;
			if(parent->color == RED) {
				//pass test
				//test case: {8, 4, 10, 2, 6, 9, 11, 1, 3, 5, 7}; delete 3;
				std::cout << "rebalance, case 2.2.1" << std::endl;
				parent->color = BLACK;
				updateGrandParent(parent, sibling, pathTo);
				parent->color = RED;
			}
			else {
				//pass test
				//test case: {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15}; delete 9;
				std::cout << "rebalance, case 2.2.2" << std::endl;
				//propogate...
				Node<T>* grandParent = updateGrandParent(parent, sibling, pathTo);
				parent->color = RED;
				rebalance(sibling, grandParent, pathTo);
			}		
		}
	}
}

#endif
