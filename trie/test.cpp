#include <iostream>

int main()
{
	int* a[10];
	for(int i = 0; i < 10; ++i)
	{
		a[i] = NULL;
	}
	if( a[0] == NULL )
	{
		std::cout << "a is null pointer" << std::endl;
	}
	else
	{
		std::cout << "a is not null pointer" << std::endl;
		std::cout << " a[0] is " << a[0] << " *a[0] is " << *a[0] << std::endl;
	}
	return 0;
}
