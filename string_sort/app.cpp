#include "lsd.h"
#include "msd.h"
#include "three_way_radix.h"

int main()
{
	LSD lsd("data/input.txt");
	lsd.print();
	
	MSD msd("data/vary_length.txt");
	msd.print();

	ThreeWayRadix twr("data/vary_length.txt");
	twr.print();

	return 0;
}
