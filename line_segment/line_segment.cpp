#include "line_tree.h"
#include "line_segment.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

LineSegment::LineSegment(const std::string& file)
{
	std::ifstream infile(file);
	std::string value;
	while(getline(infile, value, ','))
	{
		std::stringstream ss(value);
		int id;
		ss >> id;
		
		ss.str();
		char d;
		getline(infile, value, ',');
		std::cout << "read d: " << value << ", " << value.length() << value[1] << std::endl;
		d = value[0];

		double x1, x2, y1, y2;
		getline(infile, value, ',');
		x1 = std::stod(value.c_str());
		std::cout << "x1: " << value << std::endl;
		
		ss.str();
		getline(infile, value, ',');
		x2 = std::stod(value.c_str());
		
		ss.str();
		getline(infile, value, ',');
		y1 = std::stod(value.c_str());
		
		ss.str();
		getline(infile, value);
		y2 = std::stod(value.c_str());
		
		std::cout << id << ", " << d << ", " << x1 << ", " << x2 << ", " << y1 << ", " << y2 << std::endl;
		if(d == 'h') {
			d_queue.push(Line(id, x1, x2, y1, y2, HORIZONTAL));
			d_queue.push(Line(id, x2, x1, y1, y2, HORIZONTAL));
		}
		else {
			d_queue.push(Line(id, x1, x2, y1, y2, VERTICAL));
		}
	}	
}

void LineSegment::sweepSearch()
{
	LineTree ptree;
	while(!d_queue.empty())
	{
		Line line = d_queue.top();
		d_queue.pop();
		std::cout << "pop line: " << line.d_id << " direction: " << line.d_type << " x1: " << line.d_x1 << " x2: " << line.d_x2 << std::endl;
		if(line.d_type == HORIZONTAL) 
		{
			if(line.d_x1 < line.d_x2)
			{
				ptree.put(line, 0);
			}
			else 
			{
				std::swap(line.d_x1, line.d_x2);
				ptree.remove(line);
			}
		}
		else
		{
			std::vector<Line> lines = ptree.range(line.d_y1, line.d_y2);
			std::cout << "Line " << line.d_id << " intersect with these lines:" << std::endl;
			for(size_t i = 0; i < lines.size(); ++i)
			{
				std::cout << lines[i].d_id << ", "; 
			}
			std::cout << std::endl;
		}
	}
}
