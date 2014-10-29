#include "node.h"

std::list<Node*> Node::getNeighbors() {
	return neighbors;
}

void Node::insertNeighbor(Node* neighbor) {
	this->neighbors.push_back(neighbor);
}

int Source::getProductionRate() {
	return this->productionRate;
}
