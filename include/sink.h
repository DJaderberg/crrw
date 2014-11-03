#pragma once
#include "node.h"

/**
 * A Node where all Elements disappear as soon as they arrive
 *
 * @author David Jäderberg
 */
class Sink : public Node {
public:
    /**
     * Create a new Sink with neighbors n
     *
     * @param n Neighbors of the new Sink 
     * @param dist Distance to each neighbor, in same order as n
	 * @param e The Element of the Sink
     */
    Sink(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, std::shared_ptr<Element> e) : Node(n, dist, e) {
	};
	/** Create a Sink with only an element
	 *
	 * @param e The Element of the Sink
	 */
    Sink(std::shared_ptr<Element> e) : Node(e) {
	};
	void takeStep(double dt);
};
