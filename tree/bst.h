#ifndef INCLUDE_BST_H
#define INCLUDE_BST_H

#include <vector>
#include <iostream>

enum Color
{
	RED,
	BLACK
};

template<class T>
struct Node
{
	T key;
	int v;
	int rank;
	Color color;
	Node* left;
	Node* right;
	Node(T key, int v, int rank);
};

template<class T>
Node<T>::Node(T key, int v, int rank): key(key), v(v), rank(rank), color(RED), left(NULL), right(NULL)
{
}

template<class T>
bool isRed(Node<T>* root)
{
	if(root == NULL) {
		return false;
	}
	return root->color == RED;
}

template<class T>
class BST
{
	public:
		BST();
		virtual void put(T key, int v);
		Node<T>* get(T key) const;
		bool contains(T key) const;
		std::vector<Node<T>* > inorder();
		Node<T>* floor(T key) const;
		Node<T>* ceiling(T key) const;

	protected:
		Node<T>* d_root;
		int d_maxDepth;

	private:
		Node<T>* put(Node<T>* root, T key, int v, int rank);
		Node<T>* get(Node<T>* root, T key) const;
		void inorder(std::vector<Node<T>* >& list, Node<T>* root, int depth);
		Node<T>* floor(Node<T>* root, T key) const;
		Node<T>* ceiling(Node<T>* root, T key) const;
};

template<class T>
BST<T>::BST(): d_root(NULL)
{
}

template<class T>
void BST<T>::put(T key, int v)
{
	d_root = put(d_root, key, v, 0);	
}

template<class T>
Node<T>* BST<T>::put(Node<T>* root, T key, int v, int rank)
{
	if(root == NULL){
		return new Node<T>(key, v, rank);
	}
	if(key < root->key){
		root->left = put(root->left, key, v, rank);
		root->rank += 1;
	}
	else if(key > root->key){
		rank = root->rank + 1;
		root->right = put(root->right, key, v, rank);
	}
	else{
		root->v = v; //update: overwrite the old value
	}
	return root;
}

template<class T>
Node<T>* BST<T>::get(T key) const
{
	return get(d_root, key);
}

template<class T>
Node<T>* BST<T>::get(Node<T>* root, T key) const
{
	if(root == NULL) {
		return NULL;
	}
	if(key < root->key) {
		return get(root->left, key);
	}
	else if(key > root->key) {
		return get(root->right, key);
	}
	return root;
}

template<class T>
bool BST<T>::contains(T key) const
{
	return get(key) != NULL;
}

template<class T>
std::vector<Node<T>* > BST<T>::inorder()
{
	std::vector<Node<T>* > list;
	d_maxDepth = 0;
	inorder(list, d_root, 0);
	std::cout << "max depth is : " << d_maxDepth << std::endl;
	return list;
}

template<class T>
void BST<T>::inorder(std::vector<Node<T>* >& list, Node<T>* root, int depth)
{
	if(root == NULL) {
		return;
	}
	inorder(list, root->left, depth+1);
	list.push_back(root);
	d_maxDepth = d_maxDepth > depth ? d_maxDepth : depth;
	inorder(list, root->right, depth+1);
}

template<class T>
Node<T>* BST<T>::floor(T key) const
{
	return floor(d_root, key);
}

template<class T>
Node<T>* BST<T>::floor(Node<T>* root, T key) const
{
	if(root == NULL) {
		return root;
	}

	if(key < root->key) {
		return floor(root->left, key);
	}
	else if(key > root->key) {
		Node<T>* t = floor(root->right, key);
		if( t != NULL ) {
			return t;
		}
	}
	return root;
}

template<class T>
Node<T>* BST<T>::ceiling(T key) const
{
	return ceiling(d_root, key);
}

template<class T>
Node<T>* BST<T>::ceiling(Node<T>* root, T key) const
{
	if(root == NULL) {
		return root;
	}

	if(key > root->key) {
		return ceiling(root->right, key);
	}
	else if(key < root->key) {
		Node<T>* t = ceiling(root->left, key);
		if( t != NULL ) {
			return t;
		}
	}
	return root;
}

#endif
