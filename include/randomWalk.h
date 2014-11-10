/** @file randomWalk.h
 * Contains declarations of RandomWalk
 */
#pragma once
#include <memory>
#include "algorithm.h"

class RandomWalkSource;
class RandomWalkSink;

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
	virtual void updateNumberOfParticles();
	std::shared_ptr<Element> element;
	std::shared_ptr<Node> node;
	std::random_device rd;
};

class RandomWalkSource : public RandomWalk {
public:
	void updateNumberOfParticles() {
		RandomWalk::updateNumberOfParticles();
		node->setNumberOfParticles(element->productionRate + node->getNumberOfParticles());
	}
};

class RandomWalkSink : public RandomWalk {
public:
	void updateNumberOfParticles() {
		node->setNumberOfParticles(0);
	}
};
