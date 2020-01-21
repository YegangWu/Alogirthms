#include "eight_queen.h"

int main()
{
	EightQueen eq(8);
	//eq.execute();
	std::stack<Position> stack;
	Position p = Position(0,0);
	bool finish = false;
	eq.execute(p, stack, finish);
	eq.print();
	return 0;
}
