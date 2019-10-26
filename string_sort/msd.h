#ifndef MSD_INCLUDE_H
#define MSD_INCLUDE_H

#include <string>
#include <vector>

class MSD
{
	public:
		MSD(const std::string& filename);
		void print();
	private:
		int d_N;
		std::vector<std::string> d_data;
		
		int index(char c);
		void sort(int lo, int hi, int d);
};

#endif
