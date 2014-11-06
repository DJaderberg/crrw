/** @file node.cpp
 * Contains definitions of functions in Node and Source classes.
 */
#include "node.h"
#include <cmath>

unsigned int Node::idCounter = 0;

std::unordered_map<unsigned int,std::shared_ptr<Node>> Node::getNeighbors() {
    return this->neighborsMap;
}

void Node::insertNeighbor(std::shared_ptr<Node> neighbor, double distance) {
    unsigned int id = neighbor->getId();
    neighborsMap[id] = neighbor;
    lengthMap[id] = distance;
	conductivityMap[id] = element->Dmin;
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
    //double capacitance = 0;
	this->updateMeanFlow();
	this->updateFlow(dt); //This depends on updateMeanFlow having already been done for the local Node
	//TODO: Do we need the capacitance for anything?
	/*
    for ( auto it : neighborsMap) {
        capacitance += (this->conductivityMap[it.first])/(this->lengthMap[it.first]);
    }
	*/
}

void Node::takeStep(double dt) {
    this->updateCapacitance();
	this->updateConductivity(dt);
    this->updateNumberOfParticles();
	this->updatePotential();
}

//Calculate the mean flow according to eq 2.16
void Node::updateMeanFlow() {
	double flow;
	for (auto n : neighborsMap) {
		flow = (this->potential - n.second->potential)*conductivityMap[n.first]/lengthMap[n.first];
		meanFlowMap[n.first] = flow;
	}
}

void Node::updateFlow(double dt) {
	for (auto n : meanFlowMap) {
		double sign = signbit(n.second);
		double mean = abs(n.second)*dt;
		std::poisson_distribution<unsigned int> rngDist(mean);
		flowMap[n.first] = sign*rngDist(rd);
	}
}

void Node::updateNumberOfParticles() {
}

void Node::updatePotential() {
    this->potential = this->numberOfParticles/this->capacitance;
}

void Node::updateCapacitance() {
	capacitance = 0;
	for (auto n : lengthMap) {
		capacitance += conductivityMap[n.first]/n.second;
	}
}

void Node::updateConductivity(double dt) {
	double value;
	for (auto n : conductivityMap) {
		value = n.second + element->q*std::pow(abs(meanFlowMap[n.first]), element->mu) - element->lambda*n.second*dt;
		conductivityMap[n.first] = std::max(value, element->Dmin);
	}
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
