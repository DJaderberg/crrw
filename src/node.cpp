/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include "node.h"

unsigned int Node::idCounter = 0;

std::list<std::shared_ptr<Node>> Node::getNeighbors() {
	return this->neighbors;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
	this->neighbors.push_front(neighbor);
	this->length.push_front(distance);
}

unsigned int Node::getId() {
    return this->id;
}


void Node::takeStep() {
	this->updateNumberOfParticles();
	this->updateConductivity();
}

void Node::updateNumberOfParticles() {
	
}

double Node::calculatePotential() {
	int size = this->neighbors.size();
	double sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += conductivity.front();
	}
	return 3;
}

void Node::updateConductivity() {
}

