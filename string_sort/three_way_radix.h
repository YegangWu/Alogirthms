#ifndef INCLUDE_THREE_WAY_RADIX_H
#define INCLUDE_THREE_WAY_RADIX_H

#include <string>
#include <vector>

class ThreeWayRadix
{
	public:
		ThreeWayRadix(const std::string& filename);
		void print();
	private:
		int d_N;
		std::vector<std::string> d_data;
		void sort(int lo, int hi, int d);
		void swap(std::string& lhs, std::string& rhs);
};

#endif
