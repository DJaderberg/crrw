/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include "node.h"

unsigned int Node::idCounter = 0;

std::unordered_map<unsigned int,std::shared_ptr<Node>> Node::getNeighbors() {
    return this->neighborsMap;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
    unsigned int id = neighbor->getId();
    neighborsMap[id] = neighbor;
    lengthMap[id] = distance;
}

unsigned int Node::getId() {
    return this->id;
}

unsigned int Node::getNumberOfParticles() {
	return this->numberOfParticles;
}

double Node::getMeanFlow(unsigned int id) {
    return this->meanFlowMap[id];
}

void Node::prepareStep(double dt) {
	double randomValue;
	for (auto n : neighborsMap) {
		double mean = numberOfParticles*dt/lengthMap[n.first]/lengthMap.size();
		std::poisson_distribution<unsigned int> rngDist(mean);
		randomValue = rngDist(rd);
		randomValue = std::min<unsigned int>(numberOfParticles, randomValue);
		numberOfParticles -= randomValue;
		changeMap[n.first] = randomValue;
	}
}

void Node::takeStep(double dt) {
    this->updateCapacitance();
    this->updateNumberOfParticles();
    this->updateConductivity();
}

void Node::updateNumberOfParticles() {
	for (auto n : neighborsMap) {
		numberOfParticles += n.second->changeMap[id];
	}
}

double Node::calculatePotential() {
    return this->numberOfParticles/this->capacitance;
}

void Node::updateCapacitance() {
}

void Node::updateConductivity() {
}

std::string Node::toString() {
    std::string str = "ID: " + std::to_string(this->id) + "\n";
    str = str + "Number of particles: " + std::to_string(this->numberOfParticles) + "\n";
    str = str + "Capacitance: " + std::to_string(this->capacitance) + "\n";
	str += "Neighbors: ";
	for (auto n : neighborsMap) {
		str += std::to_string(n.first) + ", ";
	}
	str += "\n";
    return str;
}
