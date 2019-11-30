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
	Color color;
	Node* left;
	Node* right;
	Node(T key, int v);
};

template<class T>
Node<T>::Node(T key, int v): key(key), v(v), color(RED), left(NULL), right(NULL)
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

	protected:
		Node<T>* d_root;
		int d_maxDepth;

	private:
		Node<T>* put(Node<T>* root, T key, int v);
		Node<T>* get(Node<T>* root, T key) const;
		void inorder(std::vector<Node<T>* >& list, Node<T>* root, int depth);
};

template<class T>
BST<T>::BST(): d_root(NULL)
{
}

template<class T>
void BST<T>::put(T key, int v)
{
	d_root = put(d_root, key, v);	
}

template<class T>
Node<T>* BST<T>::put(Node<T>* root, T key, int v)
{
	if(root == NULL){
		return new Node<T>(key, v);
	}
	if(key < root->key){
		root->left = put(root->left, key, v);
	}
	else if(key > root->key){
		root->right = put(root->right, key, v);
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

#endif
