#include "node.h"

std::list<Node*> Node::getNeighbors() {
	return neighbors;
}

Node* Node::construct(std::list<Node*> neighbors) {
	return new Node(neighbors);
}

Node* Node::construct() {
	return new Node();
}

void Node::insertNeighbor(Node* neighbor) {
	this->neighbors.push_back(neighbor);
}

int Source::getProductionRate() {
	return this->productionRate;
}
