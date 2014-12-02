
#pragma once
#include "positionedNodeSet.h"

/**
 * Creates a new PositionedNodeSet with a smaller number of PositionedNodes.
 *
 * @param old The set to create the new set from
 * @param distance The maximal distance within which two nodes should be 
 * reduced to one node.
 * @return A new PositionedNodeSet, with a smaller number of Nodes
 */
std::shared_ptr<PositionedNodeSet> reduceNodes(std::shared_ptr<PositionedNodeSet> old, double distance);

