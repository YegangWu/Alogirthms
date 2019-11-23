#include "huffman.h"
#include <fstream>
#include <queue>
#include <iostream>
#include <sstream>
#include <cmath>

HuffMan::HuffMan(const std::string& filename): d_input(filename)
{
}

void HuffMan::readInput()
{
	std::ifstream infile(d_input);
	std::getline(infile, d_content);
	std::cout << d_content << std::endl;
	d_root = buildBinaryTrie();
	printTrie();
}

Node* HuffMan::buildBinaryTrie()
{
	countChar();

	std::priority_queue<Node*, std::vector<Node*>, greater > minNodeQ;
	std::map<char, int>::const_iterator it = d_charCount.begin();
	for(; it != d_charCount.end(); ++it)
	{
		minNodeQ.push(new Node(it->first, it->second, NULL, NULL));
	}

	while(minNodeQ.size() > 1)
	{
		Node* left = minNodeQ.top();
		minNodeQ.pop();
		Node* right = minNodeQ.top();
		minNodeQ.pop();
		
		std::cout << "merge " << left->d_c << " with " << left->d_freq <<  " and " << right->d_c << " with " << right->d_freq << std::endl;	
		int freq = left->d_freq + right->d_freq;
		Node* aggregate = new Node('\0', freq, left, right);
		minNodeQ.push(aggregate);
	}
	return minNodeQ.top();
}

void HuffMan::countChar()
{
	for(size_t i = 0; i < d_content.length(); ++i)
	{
		char c = d_content[i];
		if(d_charCount.find(c) == d_charCount.end())
		{
			d_charCount[c] = 1;
		}
		else
		{
			++d_charCount[c];
		}
	}
	printCount();
}

void HuffMan::printTrie()
{
	get(d_root, "");
}

void HuffMan::get(Node* p, std::string code)
{
	if(p == NULL) return;
	if(p->left == NULL && p->right == NULL){
		std::cout << p->d_c << ": " << code << std::endl;
		d_dict[p->d_c] = code;
		return;
	}
	if(p->left != NULL)
	{
		Node* left = p->left;
		get(left, code + "0");
	}
	if(p->right != NULL)
	{
		Node* right = p->right;
		get(right, code + "1");
	}
}

void HuffMan::printCount()
{
	std::map<char, int>::const_iterator it = d_charCount.begin();
	for(; it != d_charCount.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void HuffMan::encode()
{
	readInput();

	std::ofstream wfile("data/encode.txt");
	std::cout << "c is " << charToBitString('c') << std::endl;
	writeTrie(wfile, d_root);

	for(size_t i = 0; i < d_content.length(); ++i)
	{
			char c = d_content[i];
			wfile << d_dict[c];
	}	
}

std::string HuffMan::charToBitString(char c)
{
	std::stringstream bits;
	int big = (1 << 7);
	for(int i = 0; i < 8; ++i)
	{
		bits << bool((c << i) & big) ;
	}
	return bits.str();
}

char HuffMan::readChar(std::ifstream& is)
{
	int bit = 0;
	char c;
	for(int i = 0; i < 8; ++i)
	{
		is >> c;
		if( c == '1')
		{
			bit += (1 << (7-i));
		}
	}
	std::cout << "read " << char(bit) << std::endl;
	return char(bit);
}

void HuffMan::writeTrie(std::ofstream& os, Node* node)
{
	if(node->left == NULL && node->right == NULL)
	{
		os << '1' << charToBitString(node->d_c);
	}
	else
	{
		os << '0';
		writeTrie(os, node->left);
		writeTrie(os, node->right);
	}
}

Node* HuffMan::readTrie(std::ifstream& is, Node* node)
{
	char c;
	is >> c;
	if(c == '1')
	{
		c = readChar(is);
		Node* node = new Node(c, 0, NULL, NULL);
		return node;
	}
	Node* left = readTrie(is, node);
	Node* right = readTrie(is, node);
	node = new Node('\0', 0, left, right);
	return node;
}

void HuffMan::decode()
{
	std::ifstream infile(d_input);
	d_root = readTrie(infile, d_root);

	std::ofstream wfile("data/decode.txt");
	Node* node = d_root;
	char c;
	while(infile >> c)
	{
		if(c == '0')
		{
			node = node->left;	
		}
		else
		{
			node = node->right;
		}

		if(node->left == NULL && node->right == NULL)
		{
			wfile << node->d_c;	
			node = d_root;
		}
	}
}
