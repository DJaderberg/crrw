/** @file randomWalk.h
 * Contains declarations of RandomWalk
 */
#pragma once
#include <memory>
#include "algorithm.h"

class RandomWalkSource;
class RandomWalkSink;

/**
 * Represents purely random walks, where the probability depends only on 
 * the distance between nodes.
 */
class RandomWalk : public Algorithm {
public:
	void prepareStep(double dt);
	void takeStep(double dt);
	void initialize(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
		this->element = element;
		this->node = n;
	}
	/**
	 * Create a RandomWalk object that is initialized with n and element.
	 *
	 * @param n The Node to initialize the RandomWalk with
	 * @param element The Element to initialize the Node with
	 */
	static std::shared_ptr<Algorithm> create(std::shared_ptr<Node> n, std::shared_ptr<Element> element);
	virtual ~RandomWalk() {}
protected:
	///Update the number of particles at the Node
	virtual void updateNumberOfParticles();
	///The element of the Algorithm
	std::shared_ptr<Element> element;
	///The Node that the object should work with
	std::shared_ptr<Node> node;
	///Device to get random values from
	std::random_device rd;
};

///A source in the purely random walks
class RandomWalkSource : public RandomWalk {
public:
	///Update the number of particles at the Node
	void updateNumberOfParticles() {
		RandomWalk::updateNumberOfParticles();
		node->setNumberOfParticles(element->productionRate + node->getNumberOfParticles());
	}
};

///A sink in the purely random walks
class RandomWalkSink : public RandomWalk {
public:
	///Update the number of particles at the Node
	void updateNumberOfParticles() {
		node->setNumberOfParticles(0);
	}
};
