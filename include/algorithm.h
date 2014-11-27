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
	/**
	 * Prepare to take a step
	 *
	 * @param dt The size of the step to take
	 */
	virtual void prepareStep(double dt) = 0;
	/**
	 * Take a step
	 *
	 * @param dt The size of the step to take
	 */
	virtual void takeStep(double dt) = 0;
	/**
	 * Initialize an Algorithm object
	 *
	 * @param node The Node that the Algorithm should hold
	 * @param e The Element of the Node that the Algorithm should hold
	 */
	virtual void initialize(std::shared_ptr<Node> node, std::shared_ptr<Element> element) = 0;
    
    /**
     * Sets the algorithms private random device pntr to som random device
     *
     * @param rd A shared pointer to some random device;
     */
    void setRd(std::shared_ptr<std::random_device> rd);
    
protected:
    ///Private random device
    std::shared_ptr<std::random_device> rd;
};

/**
 * A pointer to a function that when given a Node and an Element returns an Algorithm.
 */
typedef std::shared_ptr<Algorithm> (*algorithmCreator)(std::shared_ptr<Node>, std::shared_ptr<Element>);

