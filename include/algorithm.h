/** @file algorithm.h
 * Contains declarations of Algorithm
 */
#pragma once
#include <memory>
#include "node.h"

/**
 * An algorithm for implementing a walk on some graph
 *
 * This interface class expects prepareStep(), takeStep(), and initialize(...) 
 * to be implemented for all subclasses. Such a subclass can then be given to a 
 * NodeSet and the NodeSet can then be used to simulate the walking supplied 
 * by this Algorithm.
 */
class Algorithm {
public:
	virtual void prepareStep(double dt) = 0;
	virtual void takeStep(double dt) = 0;
	virtual void initialize(std::shared_ptr<Node> node, std::shared_ptr<Element> element) = 0;
};

typedef std::shared_ptr<Algorithm> (*algorithmCreator)();

