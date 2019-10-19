#include "edge.h"

Edge::Edge(int v, int w, double weight): d_v(v), d_w(w), d_weight(weight)
{
}

int Edge::other(int v) const
{
	return d_v == v ? d_w : d_v;
}

int Edge::either() const
{
	return d_v;
}

double Edge::weight() const
{
	return d_weight;
}
