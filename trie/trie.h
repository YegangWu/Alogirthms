#ifndef INCLUDE_TRIE_H
#define INCLUDE_TRIE_H

#include "node.h"
#include <string>
#include <vector>

class Trie
{
	public:
		Trie(const std::string& filename);
		void addKey(const std::string& key, int value);
		bool contains(const std::string& key);
		Node* get(Node* root, const std::string& key, int d);
		void deleteKey(const std::string& key);
		
		std::vector<std::string> getKeys();	
		std::string longestPrefix(const std::string& str);
		std::vector<std::string> keysWithPrefix(const std::string prefix);
	
	private:
		Node* d_root;	
		Node* put(Node* root, const std::string& key, int value, int d);
		int index(char c);
		char symbol(int n);
		Node* remove(Node* root, const std::string& key, int d);

		void dfs(Node* root, std::string& chars, std::vector<std::string>& keys);
		int getLength(Node* root, const std::string& prefix, int d);
	
};

#endif
