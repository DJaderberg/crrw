/** @file currentWalk.cpp
 * Contains definitions of functions in the class CurrentWalk
 */
#include "currentWalk.h"

void CurrentWalk::prepareStep(double dt) {
	this->updateMeanFlow();
	this->updateFlow(dt);
}

void CurrentWalk::takeStep(double dt) {
	this->updateCapacitance();
	this->updateConductivity(dt);
	this->updateNumberOfParticles();
	this->updatePotential();
}

//Calculate the mean flow according to eq 2.16
void CurrentWalk::updateMeanFlow() {
	double flow;
	for (auto n : node->getNeighbors()) {
		flow = (node->potential - n.second->potential)*conductivityMap[n.first]/node->getDistanceMap()[n.first];
		meanFlowMap[n.first] = flow;
	}
}

void CurrentWalk::updateFlow(double dt) {
	int value;
	int tempNumberOfParticles = node->getNumberOfParticles();
	for (auto n : meanFlowMap) {
		if (n.second > 0) {
			double mean = n.second*dt;
			std::poisson_distribution<int> rngDist(mean);
			value = rngDist(rd);
			node->flowMap[n.first] = std::min(tempNumberOfParticles, value);
			tempNumberOfParticles -= value;
			tempNumberOfParticles = std::max(0, tempNumberOfParticles);
		} else {
			node->flowMap[n.first] = 0;
		}
	}
}

void CurrentWalk::updateNumberOfParticles() {
	unsigned int tempNumberOfParticles = node->getNumberOfParticles();
	for (auto n : node->getNeighbors()) {
		tempNumberOfParticles -= node->flowMap[n.first];
		tempNumberOfParticles += n.second->flowMap[node->getId()];
	}
	node->setNumberOfParticles(tempNumberOfParticles);
}

void CurrentWalk::updatePotential() {
    node->potential = node->getNumberOfParticles()/this->capacitance;
}

void CurrentWalk::updateCapacitance() {
	capacitance = 0;
	for (auto n : node->getDistanceMap()) {
		capacitance += conductivityMap[n.first]/n.second;
	}
}

void CurrentWalk::updateConductivity(double dt) {
	double value;
	for (auto n : conductivityMap) {
		value = n.second + element->q*std::pow(abs(meanFlowMap[n.first]), element->mu) - element->lambda*n.second*dt;
		conductivityMap[n.first] = std::max(value, element->Dmin);
	}
}

