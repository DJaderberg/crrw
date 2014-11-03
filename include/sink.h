#pragma once
#include "node.h"

/**
 * A Node where all Elements disappear as soon as they arrive
 *
 * @author David Jäderberg
 */
class Sink : public Node {
public:
    Sink(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, std::shared_ptr<Element> e) : Node(n, dist, e) {
	};
    Sink(std::shared_ptr<Element> e) : Node(e) {
	};
	void takeStep(double dt);
};
