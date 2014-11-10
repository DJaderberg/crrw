/** @file randomWalk.cpp
 * Contains definitions of functions in the class RandomWalk
 */
#include "randomWalk.h"
#include "positionedSource.h"
#include "positionedSink.h"

void RandomWalk::prepareStep(double dt) {
	double randomValue;
	for (auto n : node->getNeighbors()) {
		double mean = node->getNumberOfParticles()*dt/node->getDistanceMap()[n.first]/node->getNeighbors().size();
		std::poisson_distribution<unsigned int> rngDist(mean);
		randomValue = rngDist(rd);
		randomValue = std::min<unsigned int>(node->getNumberOfParticles(), randomValue);
		node->setNumberOfParticles(node->getNumberOfParticles() - randomValue);
		node->flowMap[n.first] = randomValue;
		node->meanFlowMap[n.first] = randomValue;
	}
}

void RandomWalk::takeStep(double dt) {
    this->updateNumberOfParticles();
}

void RandomWalk::updateNumberOfParticles() {
	for (auto n : node->getNeighbors()) {
		node->setNumberOfParticles(node->getNumberOfParticles() + n.second->flowMap[node->getId()]);
	}
}

std::shared_ptr<Algorithm> RandomWalk::create(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
	std::shared_ptr<RandomWalk> a;
	if (dynamic_cast<PositionedSource<2>*>(&*n)) {
		a.reset(new RandomWalkSource());
	} else if (dynamic_cast<PositionedSink<2>*>(&*n)) {
		a.reset(new RandomWalkSink());
	} else {
		a.reset(new RandomWalk());
	}
	a->initialize(n, element);
	return a;
}
