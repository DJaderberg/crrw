#include "positionedNode.h"
#include <cmath>

template<int dimension>
void PositionedNode<dimension>::insertNeighbor(std::shared_ptr<PositionedNode<dimension>> n) {
	this->insertNeighbor(n, this->distance(n));
}

template<int dimension>
double PositionedNode<dimension>::distance(PositionedNode<dimension> n) {
	double dist = 0;
	double temp;
	for (int i = 0; i < dimension; ++i) {
		temp = (this->position[i] - n->position[i]);
		dist += temp*temp;
	}
	return sqrt(dist);
}

template<int dimension>
std::string PositionedNode<dimension>::toString() {
	std::string pos = "Position: (";
	for (auto p : position) {
		pos += std::to_string(p) + ",";
	}
	pos.pop_back();
	pos += ")\n";
	return Node::toString() + pos;
}


