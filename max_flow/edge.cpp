#include "edge.h"
#include <stdexcept>

Edge::Edge(int v, int w, double capacity): d_v(v), d_w(w), d_capacity(capacity), d_flow(0)
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

int Edge::other(int v) const
{
	if(v == d_v)
	{
		return d_w;
	}
	else if(v == d_w)
	{
		return d_v;
	}
	else
	{
		throw std::runtime_error("Edge::other:  Invalid vertex id");
	}
}

double Edge::capacity() const
{
	return d_capacity;
}

double Edge::flow() const
{
	return d_flow;
}

double Edge::residualCapacityTo(int v) const
{
	if(v == d_v)
	{
		return d_flow;
	}
	else if(v == d_w)
	{
		return d_capacity - d_flow;
	}
	else
	{
		throw std::runtime_error("Edge::residualCapacity: Invalid vertex id ");
	}
}

void Edge::addResidualFlowTo(int v, double f)
{
	if(v == d_v)
	{
		d_flow -= f;
	}
	else if(v == d_w)
	{
		d_flow += f;
	}
	else
	{
		throw std::runtime_error("Edge::addResidualFlowTo: Invalid vertex id");
	}
}
