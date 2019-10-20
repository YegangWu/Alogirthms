#include "edge.h"

Edge::Edge(int v, int w, double weight): d_v(v), d_w(w), d_weight(weight)
{
}

int Edge::from() const
{
	return d_v;
}

int Edge::to() const
{
	return d_w;
}

double Edge::weight() const
{
	return d_weight;
}
