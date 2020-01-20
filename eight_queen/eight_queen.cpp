#include "eight_queen.h"
#include <stack>
#include <iostream>

EightQueen::EightQueen(int N): d_N(N)
{
	std::vector<bool> row;
	for(int i = 0; i < N; ++i) {
		row.push_back(false);
	}
	for(int i = 0; i < N; ++i) {
		d_map.push_back(row);
	}	
}

void EightQueen::execute()
{
	int m = 0;
	int n = 0;
	std::stack<Position> states;
	while(m < d_N) {
		int i = m;
		int j = n;
		while(j < d_N) {
			if(fit(i, j)) {
				states.push(Position(i, j));
				d_map[i][j] = true;
				++m;
				n = 0;
				break;
			}
			++j;
		}
		if(i < m) {
			continue;
		}

		Position p = states.top();
		states.pop();
		d_map[p.x][p.y] = false;
		m = p.x;
		n = p.y + 1;
	}
	for(int i = 0; i < d_N; ++i) {
		for(int j = 0; j < d_N; ++j) {
			std::cout << (d_map[i][j] ? 1 : 0 ) << " ";
		}
		std::cout << std::endl;
	}
}

bool EightQueen::fit(int m, int n) {
	for(int i = m-1; i >= 0; --i) {
		if(d_map[i][n]) {
			return false;
		}
		if(n-m+i >= 0 && d_map[i][n-m+i]) {
			return false;
		}
		if(n-i+m < d_N && d_map[i][n-i+m]) {
			return false;
		}
	}
	return true;
}
