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
    PositionedNode(std::shared_ptr<Element> e, std::array<double, dimension> pos) : Node(e), position(pos) {};
    /** Create a PositionedNode with neighbors
     *
     * @param pos The position of the node
     * @param n Neighbors to the node
     */
    PositionedNode(std::shared_ptr<Element> e, std::array<double, dimension> pos, std::unordered_map<unsigned int,std::shared_ptr<PositionedNode>> n) : Node(e), position(pos) {
        for (auto& neighbor : n) {
            this->insertNeighbor(neighbor);
        }
    };
    /**
     * Create a new neighbor of the node
     *
     * @param n The PositionedNode to be the new neighbor
     */
    void insertNeighbor(std::shared_ptr<PositionedNode> n);
private:
    ///Position of the node
    std::array<double, dimension> position;
    /**
     * Calculate the distance from this node to the other
     *
     * @param n The other node
     * @return The Euclidean distance between the nodes
     */
    double distance(PositionedNode<dimension> n);
};