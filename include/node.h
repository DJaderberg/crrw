/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#include <list>

/**
 * A node containing some number of elements
 */
class Node {
	public:
		Node(std::list<Node*> n) : neighbors(n) {};
		Node() {};
		/**
		 * Gets the neighbors
		 *
		 * @return A std::list of all neighbors to the Node.
		 */
		virtual std::list<Node*> getNeighbors();
		/**
		 * Create a new node 
		 *
		 * @param neighbors List of neighbors to the new node
		 * @return The new Node
		 */
		static Node* construct(std::list<Node*> neighbors);
		/**
		 * Create a new node without neighbors
		 *
		 * @return The new Node (no neighbors)
		 */
		virtual Node* construct();
		/**
		 * Add a new neighbor to the Node
		 *
		 * @param neighbor A Node that should be a neighbor to the current Node
		 */
		virtual void insertNeighbor(Node* neighbor);
	private:
		std::list<Node*> neighbors;
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
		Source(std::list<Node*> n, int p) : Node(n), productionRate(p) {};
		/**
		 * Create a Source without neighbors
		 *
		 * @param p The production rate of the source
		 */
		Source(int p) : productionRate(p) {};
		Source(std::list<Node*> n) : Node(n) {};
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


