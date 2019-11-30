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
	private:
		Node<T>* put(Node<T>* root, T key, int v);
		Node<T>* rightRotate(Node<T>* root);
		Node<T>* leftRotate(Node<T>* root);
		void reverseColor(Node<T>* root);
};

template<class T>
RedBlackTree<T>::RedBlackTree(): BST<T>()
{
}

template<class T>
void RedBlackTree<T>::put(T key, int v)
{
	BST<T>::d_root = put(BST<T>::d_root, key, v);
}

template<class T>
Node<T>* RedBlackTree<T>::put(Node<T>* root, T key, int v)
{
	if(root == NULL) {
		return new Node<T>(key, v);
	}
	if(key < root->key)
	{
		root->left = put(root->left, key, v);
	}
	else if(key > root->key)
	{
		root->right = put(root->right, key, v);
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
	root->left->color = BLACK;
	root->right->color = BLACK;
	root->color = RED;
}

#endif
