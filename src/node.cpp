/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include "node.h"

std::list<std::shared_ptr<Node>> Node::getNeighbors() {
	return this->neighbors;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
	this->neighbors.push_front(neighbor);
	this->length.push_front(distance);
}


