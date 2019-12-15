#ifndef INCLUDE_RED_BLACK_TREE_H
#define INCLUDE_RED_BLACK_TREE_H

#include "bst.h"
#include <iostream>

template<class T>
class RedBlackTree: public BST<T>
{
	public:
		RedBlackTree();
		virtual void put(T key, int v);	
		void remove(T key);	
		Node<T>* successor(T key, Node<T>** parent);
	private:
		Node<T>* put(Node<T>* root, T key, int v, int rank);
		Node<T>* rightRotate(Node<T>* root);
		Node<T>* leftRotate(Node<T>* root);
		void reverseColor(Node<T>* root);

		Node<T>* get(T key, Node<T>* parent);
		Node<T>* successor(Node<T>* root, T key, Node<T>** parent);
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
Node<T>* RedBlackTree<T>::get(T key, Node<T>* parent)
{
	Node<T>* t = BST<T>::d_root;
	parent = NULL;
	while(t != NULL)
	{
		if(key == t->key) {
			return t;
		}
		else {
			parent = t;
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
Node<T>* RedBlackTree<T>::successor(T key, Node<T>** parent)
{
	return successor(BST<T>::d_root, key, parent);
}

template<class T>
Node<T>* RedBlackTree<T>::successor(Node<T>* root, T key, Node<T>** parent)
{
	if(root == NULL) {
		return NULL;
	}
	if(key >= root->key) {
		if(root->right != NULL) {
			*parent = root;
		}
		return successor(root->right, key, parent);
	}
	else {
		Node<T>* parentOld = *parent;
		*parent = root;
		Node<T>* t = successor(root->left, key, parent);
		if(t == NULL) {
			*parent = parentOld;
			return root;
		}
		return t;
	}
}

template<class T>
void RedBlackTree<T>::remove(T key)
{
	Node<T>* t;
	Node<T>* parent;
	t = get(key, parent);
	if(t == NULL) {
		std::cout << "Node " << key << " doesn't exist, nothing to be removed." << std::endl;
		return;
	}

	//case 1, t->left = t->right = null
	if(t->left == NULL) { //We know that t->right = null. Why? Because it's a left-ligning red-black tree.
		if(t == parent->right) {
			delete t;
			return;
		}
		else {
			if(t->color == RED) {
				delete t;
				return;
			}
			else {
				delete t;
				Node<T>* y = parent->right;
				if(y->left == NULL) { 
					parent->left = y;
					parent->right = NULL;
				}
				else {
					y->left->left = parent;
					y->left->left->color = RED;
					y->left->color = y->color;
					y->color = parent->color;
					parent = y;
				}
			}
		}
	}
	else if(t->right == NULL) {
		if(t == parent->left) {
			parent->left = t->left;
		}
		else {
			parent->right = t->left;
		}
		t->left->color = t->color;
		delete t;
	}
	else {
		Node<T>* ceilingParent;
		Node<T>* ceiling = successor(t->key, ceilingParent);
		assert(ceilingParent != NULL);
		assert(ceiling != NULL);
		assert(ceiling->left == NULL);
		assert(ceiling->right == NULL);
		if(ceiling == ceilingParent->left) {
			ceilingParent->left = NULL;
		}
		else {
			ceilingParent->right = NULL;
		}
		if(t == parent->left) {
			parent->left = ceiling;
		}
		else {
			parent->right = ceiling;
		}
		ceiling->left = t->left;
		ceiling->right = t->right;
		delete t;
	}
} //this function is incomplete. 

#endif
