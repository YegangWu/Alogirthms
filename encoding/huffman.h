#ifndef INCLUDE_HUFFMAN_H
#define INCLUDE_HUFFMAN_H

#include <string>
#include <map>
#include "node.h"

class HuffMan
{
	public:
		HuffMan(const std::string& filename);
		void encode();

		void decode();
	private:
		std::string d_input;
		Node* d_root;
		std::string d_content;
		std::map<char, int> d_charCount;
		std::map<char, std::string> d_dict;

		void readInput();
		void countChar();
		Node* buildBinaryTrie();
		void printCount();
		void printTrie();
		void get(Node*, std::string code);

		std::string charToBitString(char c);
		char readChar(std::ifstream& is);

		void writeTrie(std::ofstream& os, Node* node);
		Node* readTrie(std::ifstream& is, Node* node);
	
};

#endif
