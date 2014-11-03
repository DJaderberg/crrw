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
    
    //this->neighbors.push_front(neighbor);
    //this->length.push_front(distance);
}

unsigned int Node::getId() {
    return this->id;
}


void Node::takeStep() {
    this->updateNumberOfParticles();
    this->updateConductivity();
}

void Node::updateNumberOfParticles() {
    this->calculatePotential();
}

double Node::calculatePotential() {
    double sum = 0;
    
    for ( auto it = neighborsMap.begin(); it != neighborsMap.end(); ++it ) {
        std::cout << " " << it->first << ":" << it->second;
        // TODO: Caculate the potential
    }
    
    return sum;
}

void Node::updateConductivity() {
}
