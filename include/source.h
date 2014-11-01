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
		Source(std::list<std::shared_ptr<Node>> n, std::list<double> dist, int p) : Node(n, dist), productionRate(p) {};
		/**
		 * Create a Source without neighbors
		 *
		 * @param p The production rate of the source
		 */
		Source(int p) : productionRate(p) {};
		/**
		 * Create a new Source with neighbors n and production rate 0
		 */
		Source(std::list<std::shared_ptr<Node>> n, std::list<double> dist) : Node(n, dist) {};
		Source() {};
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


