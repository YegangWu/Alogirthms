#include <iostream>

int main()
{
	double v1 = 3.21654;
	double v2 = 3.21654;
	if(v1 == v2) std::cout << "equal!";
	else if(v1 < v2) std::cout << "v1 less than v2!";
	else std::cout << "v1 greater than v2!";
	std::cout << std::endl;
	return 0;
}
