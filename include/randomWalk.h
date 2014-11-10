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
private:
	std::shared_ptr<Element> element;
	std::shared_ptr<Node> node;
};
