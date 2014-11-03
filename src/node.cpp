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


void Node::takeStep() {
    this->updateCapacitance();
    this->updateNumberOfParticles();
    this->updateConductivity();
}

void Node::updateNumberOfParticles() {
    this->calculatePotential();
}

double Node::calculatePotential() {
    return this->numberOfParticles/this->capacitance;
}

void Node::updateCapacitance() {
    double sum = 0;
    for ( auto it = neighborsMap.begin(); it != neighborsMap.end(); ++it ) {
        sum += (this->conductivityMap[it->first] + it->second->conductivityMap[this->id])/(this->lengthMap[it->first]);
    }
    this->capacitance = sum;
}

void Node::updateConductivity() {
}

std::string Node::toString() {
    std::string str = "ID: " + std::to_string(this->id) + "\n";
    str = str + "Number of particles: " + std::to_string(this->numberOfParticles) + "\n";
    str = str + "Capacitance: " + std::to_string(this->capacitance) + "\n";
    return str;
}
