#include "interval_tree.h"
#include <fstream>
#include <sstream>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

Line::Line(int id, double lo, double hi, double x, double max, bool start): id(id), lo(lo), hi(hi), x(x), max(max), start(start)
{
}

IntervalTree::IntervalTree(const std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	while(getline(infile, line))
	{
		std::stringstream ss(line);
		std::cout << "read line " << line << std::endl;
		int id;
		double lo, hi, x, max;
		std::string type;
		ss >> id >> lo >> hi >> x >> type;
		max = hi;
		std::cout << "id: " << id << ", lo: " << lo << ", hi: " << hi 
				  << ", x: " << x << ", max: " << max << ", type: " << type 
				  << std::endl;
		std::cout << "ss.str() is " << ss.str() << std::endl;
		if(type == "S")
		{
			d_queue.push(Line(id, lo, hi, x, max, true));
		}
		else if(type == "E")
		{
			d_queue.push(Line(id, lo, hi, x, max, false));
		}
		else
		{
			assertm(false, "Invalid input");
		}
	}
}

void IntervalTree::sweep()
{
	std::vector<int> overlaps;
	while(!d_queue.empty())
	{
		Line line = d_queue.top();
		d_queue.pop();
		
		if(!line.start)	
		{
			remove(line);
		}

		overlaps.clear();
		searchOverlaps(line, overlaps);
		std::cout << "rectangle " << line.id << " overlaps with these rectangles: ";
		for(size_t i = 0; i < overlaps.size(); ++i)
		{
			std::cout << overlaps[i] << ", ";
		}
		std::cout << std::endl;
		if(line.start)
		{
			put(line, 0);
		}
	}
	
}


void IntervalTree::searchOverlaps(const Line& line, std::vector<int>& overlaps)
{
	searchOverlaps(d_root, line, overlaps);	
}

void IntervalTree::searchOverlaps(Node<Line>* root, const Line& line, std::vector<int>& overlaps)
{
	if(root == NULL)
	{
		return;
	}

	Line key = root->key;
	std::cout << "compare line " << line.id << " with line " << key.id << std::endl;
	if( !(line.hi < key.lo || line.lo > key.hi) )
	{
		overlaps.push_back(key.id);
	}
	
	searchOverlaps(root->left, line, overlaps);
	if(line.hi > key.lo)
	{
		searchOverlaps(root->right, line, overlaps);
	}
}

void IntervalTree::put(Line key, int v)
{
	BST<Line>::d_root = put(BST<Line>::d_root, key, v, 0);
}

Node<Line>* IntervalTree::put(Node<Line>* root, Line line, int v, int rank)
{
	if(root == NULL)
	{
		return new Node<Line>(line, v, rank);
	}
	if(d_root->key.max < line.hi)
	{
		d_root->key.max = line.hi;
	}

	if(line < root->key)
	{
		root->left = put(root->left, line, v, rank);
	}
	else if(line > root->key)
	{
		root->right = put(root->right, line, v, rank);
	}
	else
	{
		root->v = v;
	}

	if(isRed<Line>(root->right) && !isRed<Line>(root->left)) {
		root = leftRotate(root);
	}
	if(isRed<Line>(root->left) && isRed<Line>(root->left->left)) {
		root = rightRotate(root);
	}
	if(isRed<Line>(root->left) && isRed<Line>(root->right)) {
		reverseColor(root);
	}	
	return root; 
}
