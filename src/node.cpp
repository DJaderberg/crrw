/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include "node.h"
#include <cmath>
#include <algorithm>

unsigned long long Node::idCounter = 0;

std::unordered_map<unsigned long long,std::shared_ptr<Node>> Node::getNeighbors() {
    return this->neighborsMap;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
    unsigned long long id = neighbor->getId();
    neighborsMap[id] = neighbor;
    lengthMap[id] = distance;
}

void Node::insertNeighborUnique(std::shared_ptr<Node> neighbor, double distance) {
		if (neighborsMap.count(neighbor->getId()) || neighbor->getId() == getId()) {
			return;
		} else {
			insertNeighbor(neighbor, distance);
		}
}

unsigned long long Node::getId() {
    return this->id;
}

long long Node::getFileId() {
    return this->fileId;
}

void Node::setFileId(long long fileId) {
    this->fileId = fileId;
}

unsigned long long Node::getNumberOfParticles() {
	return this->numberOfParticles;
}

std::string Node::toString() {
    std::string str = "ID: " + std::to_string(this->id) + "\n";
    str = str + "Number of particles: " + std::to_string(this->numberOfParticles) + "\n";
	str += "Neighbors and mean flow: ";
	for (auto n : meanFlowMap) {
		str += std::to_string(n.first) + ": " + std::to_string(n.second) + ", ";
	}
	str += "\n";
    str += "Neighbors and conductivity: ";
    for (auto n : conductivityMap) {
        str += std::to_string(n.first) + ": " + std::to_string(n.second) + ", ";
    }
    str += "\n";
    
    return str;
}
