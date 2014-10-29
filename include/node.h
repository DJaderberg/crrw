/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#include <list>
#include <memory>

/**
 * A node containing some number of elements
 */
class Node {
	public:
		/**
		 * Create a new Node with neighbors n
		 * @param n Neighbors of the new Node
		 */
		Node(std::list<std::shared_ptr<Node>> n) : neighbors(n) {};
		Node() {};
		/**
		 * Gets the neighbors
		 *
		 * @return A std::list of all neighbors to the Node.
		 */
		virtual std::list<std::shared_ptr<Node>> getNeighbors();
		/**
		 * Add a new neighbor to the Node
		 *
		 * @param neighbor A Node that should be a neighbor to the current Node
		 */
		virtual void insertNeighbor(std::shared_ptr<Node> neighbor);
	private:
		std::list<std::shared_ptr<Node>> neighbors;
};

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
		 * @param p The production rate of the Source
		 */
		Source(std::list<std::shared_ptr<Node>> n, int p) : Node(n), productionRate(p) {};
		/**
		 * Create a Source without neighbors
		 *
		 * @param p The production rate of the source
		 */
		Source(int p) : productionRate(p) {};
		Source(std::list<std::shared_ptr<Node>> n) : Node(n) {};
		Source() {};
		/**
		 * Get the production rate of this Source
		 *
		 * @return How many elements are produced by this Source during one time unit
		 */
		int getProductionRate();
	private:
		int productionRate = 0;
};


