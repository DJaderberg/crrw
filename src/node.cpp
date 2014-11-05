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

void Node::prepareStep(double dt) {
    double capacitance = 0;
	this->updateMeanFlow();
	this->updateFlow(); //This depends on updateMeanFlow having already been done for the Node
    for ( auto it : neighborsMap) {
        capacitance += (this->conductivityMap[it.first])/(this->lengthMap[it.first]);
    }
	
	for (auto it : neighborsMap) {

	}
}

void Node::takeStep(double dt) {
    this->updateCapacitance();
    this->updateNumberOfParticles();
    this->updateConductivity();
	this->updatePotential();
}

//Calculate the mean flow according to eq 2.16
void Node::updateMeanFlow() {
	unsigned int neighborNumberOfParticles;
	double flow;
	for (auto n : neighborsMap) {
		neighborNumberOfParticles = n.second->getNumberOfParticles();
		flow = (this->potential - n.second->potential)*conductivityMap[n.first]/lengthMap[n.first];
		meanFlowMap[n.first] = flow;
	}
}

void Node::updateFlow() {
}

void Node::updateNumberOfParticles() {
}

void Node::updatePotential() {
    this->potential = this->numberOfParticles/this->capacitance;
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
