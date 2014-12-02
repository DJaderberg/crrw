#pragma once
#include "node.h"

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
    PositionedNode(std::array<double, dimension> pos) : Node(), position(pos) {};
    /** Create a PositionedNode with neighbors
     *
     * @param pos The position of the node
     * @param n Neighbors to the node
	 * @param e The Element of the Node
     */
    PositionedNode(std::array<double, dimension> pos, std::unordered_map<unsigned int,std::shared_ptr<PositionedNode>> n) : Node(), position(pos) {
        for (auto& neighbor : n) {
            this->insertNeighbor(neighbor);
        }
    };
    /**
     * Create a new neighbor of the node
     *
     * @param n The PositionedNode to be the new neighbor
     */
    void insertNeighbor(std::shared_ptr<PositionedNode<dimension>> n) {
		Node::insertNeighbor(n, this->distance(n));
	}
	/**
	 * Create a new neighbor of the node if the node is not already connected 
	 * to the given neighbor.
	 */
	void insertNeighborUnique(std::shared_ptr<PositionedNode<dimension>> n) {
		Node::insertNeighborUnique(n, this->distance(n));
	}
	std::string toString() {
		std::string pos = "Position: (";
		for (auto p : position) {
			pos += std::to_string(p) + ",";
		}
		pos.pop_back();
		pos += ")\n";
		return Node::toString() + pos;
	}
	///Get position
	std::array<double, dimension> getPosition() {
		return position;
	}
    /**
     * Calculate the distance from this node to the other
     *
     * @param n The other node
     * @return The Euclidean distance between the nodes
     */
    double distance(std::shared_ptr<PositionedNode<dimension>> n) {
		double dist = 0;
		double temp;
		for (int i = 0; i < dimension; ++i) {
			temp = (this->position[i] - n->position[i]);
			dist += temp*temp;
		}
		return sqrt(dist);
	}
private:
    ///Position of the node
    std::array<double, dimension> position;
};
