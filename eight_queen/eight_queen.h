#ifndef INCLUDE_EIGHT_QUEEN_H
#define INCLUDE_EIGHT_QUEEN_H

#include <vector>
#include <stack>

struct Position
{
	Position(int x, int y): x(x), y(y) {}
	int x;
	int y;
};

class EightQueen
{
	public:
		EightQueen(int N = 8);
		void execute();
		void execute(const Position& p, std::stack<Position>& stack, bool& finish);
		void print();
	private:
		int d_N;
		std::vector<std::vector<bool> > d_map;
		bool fit(int m, int n);
		bool rowSearch(int m, int& n, std::stack<Position>& stack);
};

#endif
