/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#include <list>
#include <memory>
#include <array>

/**
 * A node containing some number of elements
 *
 * @author David Jäderberg
 */
class Node {
	public:
		/**
		 * Create a new Node with neighbors n
		 *
		 * @param n Neighbors of the new Node
		 * @param dist Distance to each neighbor, in same order as n
		 */
		Node(std::list<std::shared_ptr<Node>> n, std::list<double> dist) : neighbors(n), length(dist) {};
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
		virtual void insertNeighbor(std::shared_ptr<Node> neighbor, double distance);
		/**
		 * Allow elements at node to move, if needed
		 */
		void takeStep();
		virtual ~Node() {
		}
	private:
		/**
		 * A list containing all neighbors of the Node.
		 */
		std::list<std::shared_ptr<Node>> neighbors;
		///The 'length in space' to all neighbors of the node
		std::list<double> length;
		///Number of elements at the node
		double potential = 0; //TODO: Should this be unsigned int?
		///Flow rate through the node
		std::list<double> current;
		///Conductivity of the node
		std::list<double> conductivity;
		///Capacitance of the node
		double capacitance = 0;
		///Reinforcement intensity
		constexpr static double q = 0.0001;
		///Conductivity decrease rate
		constexpr static double lambda = 0.001;
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


/**
 * A node with a position in space
 *
 * @tparam dimension Dimensionality of the Euclidean space that the node exists in
 */
template<int dimension>
class PositionedNode : public Node {
	public:
		/**
		 * Create a PositionedNode
		 *
		 * @param pos The position
		 */
		PositionedNode(std::array<double, dimension> pos) : position(pos) {};
		/**
		 * Create a new neighbor of the node
		 *
		 * @param n The PositionedNode to be the new neighbor
		 */
		void insertNeighbor(std::shared_ptr<PositionedNode> n);
	private:
		///Position of the node
		std::array<PositionedNode, dimension> position;
		/**
		 * Calculate the distance from this node to the other
		 *
		 * @param n The other node
		 * @return The Euclidean distance between the nodes
		 */
		double distance(PositionedNode<dimension> n);
};
