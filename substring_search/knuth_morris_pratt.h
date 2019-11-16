#ifndef KNUTH_MORRIS_PRETT_H
#define KNUTH_MORRIS_PRETT_H

#include <string>
#include <vector>

class KMP
{
	public:
		KMP(const std::string& target, const std::string& pattern);
		void print();
	private:
		std::vector<std::vector<int> > d_dict;
		int d_n;
		int d_R;
		int d_start;
		bool d_found;

		int toInt(char c);
};

#endif
