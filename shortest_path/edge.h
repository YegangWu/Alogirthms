#ifndef INCLUDE_EDGE_H
#define INCLUDE_EDGE_H

class Edge
{
	public:
		Edge(int v, int w, double weight);
		int from() const;
		int to() const;
		double weight() const;
	private:
		int d_v;
		int d_w;
		double d_weight;
};

#endif
