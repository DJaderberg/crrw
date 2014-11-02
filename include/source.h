#pragma once
#include "node.h"

/**
 * A node that produces a number of elements during each time step
 *
 * @author David Jäderberg
 */
class Source : public Node {
public:
    /**
     * Create a Source with neighbors and a production rate
     * @param n All neighbors to the Source
     * @param dist Distance to all neighbors of the source
     * @param p The production rate of the Source
     */
    Source(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, std::shared_ptr<Element> e, int p) : Node(n, dist, e), productionRate(p) {};
    /**
     * Create a Source without neighbors
     *
     * @param p The production rate of the source
     */
    Source(int p, std::shared_ptr<Element> e) : Node(e), productionRate(p) {};
    /**
     * Create a new Source with neighbors n and production rate 0
     */
    Source(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, std::shared_ptr<Element> e) : Node(n, dist, e) {};
    /**
     * Get the production rate of this Source
     *
     * @return How many elements are produced by this Source during one time unit
     */
    int getProductionRate();
private:
    /**
     * The production rate of the Source
     *
     * Any source with a negative production rate can be considered as
     * a sink.
     */
    int productionRate = 0;
};


