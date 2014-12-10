/** @file currentWalk.cpp
 * Contains definitions of functions in the class CurrentWalk
 */
#include "currentWalk.h"

std::random_device CurrentWalk::rd;

void CurrentWalk::prepareStep(double dt) {
	this->updateMeanFlow();
	this->updateFlow(dt);
}

void CurrentWalk::takeStep(double dt) {
	this->updateConductivity(dt);
	this->updateCapacitance();
	this->updateNumberOfParticles(dt);
	this->updatePotential();
}

void CurrentWalk::reinitialize() {
    this->updateCapacitance();
    this->updatePotential();
	this->updateMeanFlow();
}

//Calculate the mean flow according to eq 2.16
void CurrentWalk::updateMeanFlow() {
	double flow;
	for (auto n : node->getNeighbors()) {
		flow = (node->potential - n.second->potential)*conductivityMap[n.first]/node->getDistanceMap()[n.first];
		node->meanFlowMap[n.first] = flow;
	}
}

void CurrentWalk::updateFlow(double dt) {
	int value;
	int tempNumberOfParticles = node->getNumberOfParticles();
	for (auto n : node->meanFlowMap) {
		if (n.second > 0) {
			double mean = n.second*dt;
			std::poisson_distribution<int> rngDist(mean);
			value = rngDist(this->rd);
			node->flowMap[n.first] = std::min(tempNumberOfParticles, value);
			tempNumberOfParticles -= value;
			tempNumberOfParticles = std::max(0, tempNumberOfParticles);
		} else {
			node->flowMap[n.first] = 0;
		}
	}
}

void CurrentWalk::updateNumberOfParticles(double dt) {
	unsigned int tempNumberOfParticles = node->getNumberOfParticles();
	for (auto n : node->getNeighbors()) {
		tempNumberOfParticles -= node->flowMap[n.first];
		tempNumberOfParticles += n.second->flowMap[node->getId()];
	}
	node->setNumberOfParticles(tempNumberOfParticles);
}

void CurrentWalk::updatePotential() {
    node->potential = ((double)node->getNumberOfParticles())/this->capacitance;
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
        value = n.second + element->q*std::pow(std::abs(node->meanFlowMap[n.first]), element->mu) - element->lambda*n.second*dt;
		conductivityMap[n.first] = std::max(value, element->Dmin);
	}
}

std::shared_ptr<Algorithm> CurrentWalk::create(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
	std::shared_ptr<CurrentWalk> a;
	//TODO: Also check for non-positioned Sink/Source
	if (dynamic_cast<PositionedSource<2>*>(&*n)) {
		a.reset(new CurrentWalkSource());
	} else if (dynamic_cast<PositionedSink<2>*>(&*n)) {
		a.reset(new CurrentWalkSink());
	} else {
		a.reset(new CurrentWalk());
	}
	a->initialize(n, element);
	return a;
}
