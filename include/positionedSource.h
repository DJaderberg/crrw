/** @file positionedSource.h
 * Contains declaration of the class PositionedSource
 */
#pragma once
#include "source.h"
#include "positionedNode.h"
#include <memory>

/**
 * A Source with a position in space
 * 
 * @tparam dimension Dimensionality of the Euclidean space that the node exists in
 */
template<int dimension>
class PositionedSource : public Source, public PositionedNode<dimension> {
	/**
	 * Create a PositionedSource
	 *
	 * @param pos The position of the Source
	 * @param e The Element of the Source
	 * @param p The production rate of the Source
	 */
	PositionedSource(std::shared_ptr<Element> e, std::array<double, dimension> pos, int p) : Node(e), PositionedNode<dimension>(e, pos), Source(p, e) {
	};
};
