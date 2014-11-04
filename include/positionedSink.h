/** @file positionedSink.h
 * Contains declaration of the class PositionedSink
 */
#pragma once
#include "sink.h"
#include "positionedNode.h"
#include <memory>

/**
 * A Sink with a position in space
 * 
 * @tparam dimension Dimensionality of the Euclidean space that the node exists in
 */
template<int dimension>
class PositionedSink : public Sink, public PositionedNode<dimension> {
	/**
	 * Create a PositionedSink
	 *
	 * @param pos The position of the Sink
	 * @param e The Element of the Sink
	 */
	PositionedSink(std::shared_ptr<Element> e, std::array<double, dimension> pos) : Node(e), PositionedNode<dimension>(e, pos), Sink(e) {
	};
};
