/** @file currentWalk.h
 * Contains declarations of CurrentWalk
 */
#pragma once
#include <memory>
#include "algorithm.h"
#include "antElement.h"

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
	static std::shared_ptr<Algorithm> create() {
		std::shared_ptr<Algorithm> a(new CurrentWalk());
		return a;
	}
private:
	void updateMeanFlow();
	void updateFlow(double dt);
	void updateConductivity(double dt);
	void updateCapacitance();
	void updateNumberOfParticles();
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

