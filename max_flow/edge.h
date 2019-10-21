#ifndef INCLUDE_EDGE_H
#define INCLUDE_EDGE_H

class Edge
{
	public:
		Edge(int v, int w, double capacity);
		int from() const;
		int to() const;
		int other(int v) const;
		double flow() const;
		double capacity() const;
		double residualCapacityTo(int v) const;
		void addResidualFlowTo(int v, double f);
	private:
		const int d_v;
		const int d_w;
		const double d_capacity;
		double d_flow;	
};

#endif
