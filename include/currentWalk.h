/** @file currentWalk.h
 * Contains declarations of CurrentWalk
 */
#pragma once
#include <memory>
#include "algorithm.h"
#include "antElement.h"
#include "positionedSource.h"
#include "positionedSink.h"

class CurrentWalkSource;
class CurrentWalkSink;

class CurrentWalk : public Algorithm {
public:
	void prepareStep(double dt);
	void takeStep(double dt);
	void initialize(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
		this->element = element;
		this->node = n;
		for (auto i : n->getNeighbors()) {
			conductivityMap[i.second->getId()] = element->Dmin;
		}
	}
	static std::shared_ptr<Algorithm> create(std::shared_ptr<Node> n, std::shared_ptr<Element> element);
protected:
	void updateMeanFlow();
	void updateFlow(double dt);
	void updateConductivity(double dt);
	void updateCapacitance();
	virtual void updateNumberOfParticles();
	void (*updateFunction)();
	void updatePotential();
	std::shared_ptr<Node> node;
    ///Mean flow rate through the Node
    std::unordered_map<unsigned int,double> meanFlowMap;
    ///Conductivity of the Node
    std::unordered_map<unsigned int,double> conductivityMap;
    ///Capacitance of the Node
    double capacitance = 0;
	///Random number generation state
	std::random_device rd;
    ///The element of the Algorithm
    std::shared_ptr<Element> element;
};

class CurrentWalkSource : public CurrentWalk {
public:
	void updateNumberOfParticles() {
		CurrentWalk::updateNumberOfParticles();
		node->setNumberOfParticles(element->productionRate + node->getNumberOfParticles());
	}
};

class CurrentWalkSink : public CurrentWalk {
public:
	void updateNumberOfParticles() {
		node->setNumberOfParticles(0);
	}
};
