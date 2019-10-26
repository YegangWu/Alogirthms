#ifndef INCLUDE_LSD_H
#define INCLUDE_LSD_H

#include <string>
#include <vector>

class LSD
{
	public:
		LSD(const std::string& filename);
		void sort(int d);
		int index(char c);
		void print();
		
	private:
		int d_N;
		int d_w;
		std::vector<std::string> d_data;
		std::vector<std::string> d_aux;
};

#endif
