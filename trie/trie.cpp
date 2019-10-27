#include "trie.h"
#include <fstream>
#include <sstream>
#include <iostream>

Trie::Trie(const std::string& filename)
{
	d_root = new Node;

	std::ifstream infile(filename);
	std::string line;
	std::string key;
	int value;
	while(getline(infile, line))
	{
		std::stringstream ss(line);
		ss >> key >> value;
		addKey(key, value);
	}
}

void Trie::addKey(const std::string& key, int value)
{
	d_root = put(d_root, key, value, 0);
}

int Trie::index(char c)
{
	return c - 97;
}

char Trie::symbol(int n)
{
	return n + 97;
}

Node* Trie::put(Node* root, const std::string& key, int value, int d)
{
	if( root == NULL )
	{
		root = new Node(value);
		return root;
	}
	if(d == key.length())
	{
		root->value = value;
		return root;
	}
	int n = index(key[d]);
	if( root->next[n] == NULL )
	{
		root->next[n] = new Node;
		root->next[n] = put(root->next[n], key, value, d+1); 
	}
	else
	{
		root->next[n] = put(root->next[n], key, value, d+1);
	}
	return root;
}

bool Trie::contains(const std::string& key)
{
	Node* node = get(d_root, key, 0);
	if(node == NULL || node->value == user::INVALID)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Node* Trie::get(Node* root, const std::string& key, int d)
{
	if(root == NULL)
	{
		return root;
	}
	if(d == key.length())
	{
		return root;
	}
	int n = index(key[d]);
	if(root->next[n] == NULL)
	{
		return root->next[n];
	}
	else
	{
		return get(root->next[n], key, d+1);
	}
}

void Trie::deleteKey(const std::string& key)
{
	d_root = remove(d_root, key, 0);
}

Node* Trie::remove(Node* root, const std::string& key, int d)
{
	if(root == NULL)
	{
		return root;
	}
	if( d == key.length()-1 )
	{
		int n = index(key[d]);
		if(root->next[n])
		{
			if(root->next[n]->empty())
			{
				std::cout << "character " << key[d] << " is the leaf node, will be deleted" << std::endl;
				delete root->next[n];
				root->next[n] = NULL;
				if(root->empty())
				{
					std::cout << "node " << key[d-1] << " is empty, will be removed" << std::endl;
					delete root;
					root = NULL;
				}
			}
			else
			{
				std::cout << "character " << key[d] << " is not the leaf node, will update its value only" << std::endl;
				root->next[n]->value = user::INVALID;
			}
		}
		else
		{
			std::cout << "key " << key << " doesn't exist!" << std::endl;
		}
	}
	else
	{
		int n = index(key[d]);
		if(!root->next[n])
		{
			std::cout << "key " << key << " doesn't exist!" << std::endl;
		}
		else
		{
			root->next[n] = remove(root->next[n], key, d+1);
			if(root->empty())
			{
				std::cout << "node " << key[d-1] << " is empty, will be removed" << std::endl;
				delete root;
				root = NULL;
			}
		}
	}
	return root;
}

std::vector<std::string> Trie::getKeys()
{
	std::vector<std::string> keys;
	std::string chars = "";
	dfs(d_root, chars, keys);
	return keys;
}

void Trie::dfs(Node* root, std::string& chars, std::vector<std::string>& keys)
{
	if(root == NULL)
	{
		return;
	}
	for(int i = 0; i < R; ++i)
	{
		if(root->next[i])
		{
			chars += symbol(i) ;
			if(root->next[i]->value != user::INVALID)
			{
				keys.push_back(chars);
			}
			dfs(root->next[i], chars, keys);
		}
	}
	if(!chars.empty())
	{
		chars = chars.substr(0, chars.length() - 1);
	}
}

std::string Trie::longestPrefix(const std::string& str)
{
	int L = getLength(d_root, str, 0); 
	return str.substr(0, L);	
}

int Trie::getLength(Node* root, const std::string& str, int d)
{
	int n = index(str[d]);
	if(!root->next[n])
	{
		return d;
	}
	return getLength(root->next[n], str, d+1);
}

std::vector<std::string> keysWithPrefix(const std::string& prefix)
{
	std::cout << "Not implemented!" << std::endl;
	std::vector<std::string> tmp;
	return tmp;
}
