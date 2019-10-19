#ifndef INCLUDE_EDGE_H
#define INCLUDE_EDGE_H

class Edge
{
	public:
		Edge(int v, int w, double weight);
		int other(int v) const;
		int either() const ;
		double weight() const;
	private:
		int d_v;
		int d_w;
		double d_weight;
	friend bool operator>(const Edge& lhs, const Edge& rhs);
};

inline
bool operator>(const Edge& lhs, const Edge& rhs)
{
	return lhs.d_weight > rhs.d_weight;
}

struct greaterByWeight
{
	bool operator()(const Edge& lhs, const Edge& rhs)
	{
		return lhs > rhs;
	}
};

#endif
