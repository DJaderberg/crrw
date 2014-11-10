#pragma once
#include "node.h"
#include <random>

/**
 * A node that produces a number of elements during each time step
 *
 * @author David Jäderberg
 */
class Source : public virtual Node {
public:
    /**
     * Create a Source with neighbors and a production rate
     * @param n All neighbors to the Source
     * @param dist Distance to all neighbors of the source
     * @param p The production rate of the Source
     */
    Source(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, int p) : Node(n, dist), productionRate(p) {};
    /**
     * Create a Source without neighbors
     *
     * @param p The production rate of the source
	 * @param e The Element of the Node
     */
    Source(int p) : Node(), productionRate(p) {};
    /**
     * Create a new Source with neighbors n and production rate 0
     */
    Source(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist) : Node(n, dist) {};
    /**
     * Get the production rate of this Source
     *
     * @return How many elements are produced by this Source during one time unit
     */
    int getProductionRate();
	virtual std::string toString();
private:
    /**
     * The production rate of the Source
     *
     * Any source with a negative production rate can be considered as
     * a sink.
     */
    int productionRate = 0;
	///Random number generation state
	std::random_device rd;
};


