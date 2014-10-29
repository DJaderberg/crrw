#include "node.h"

std::list<std::shared_ptr<Node>> Node::getNeighbors() {
	return this->neighbors;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor) {
	this->neighbors.push_back(neighbor);
}

int Source::getProductionRate() {
	return this->productionRate;
}
