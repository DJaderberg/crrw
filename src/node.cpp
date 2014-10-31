/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include <cmath>
#include "node.h"

std::list<std::shared_ptr<Node>> Node::getNeighbors() {
	return this->neighbors;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
	this->neighbors.push_front(neighbor);
	this->length.push_front(distance);
}

int Source::getProductionRate() {
	return this->productionRate;
}

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

