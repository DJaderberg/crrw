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
class PositionedSink : public PositionedNode<dimension> {
public:
	/**
	 * Create a PositionedSink
	 *
	 * @param pos The position of the Sink
	 * @param e The Element of the Sink
	 */
	PositionedSink(std::shared_ptr<Element> e, std::array<double, dimension> pos) : PositionedNode<dimension>(e, pos) {
	};
	///Return the id of the Sink
	unsigned int getId() {
		return ((PositionedNode<dimension> *) this)->getId();
	};
	///Take a time step
	void takeStep(double dt) {
		Node::takeStep(dt); //TODO: Is this necessary?
		this->numberOfParticles = 0;
	}
	//Return string representation of the Sink
	std::string toString() {
		return PositionedNode<dimension>::toString();
	}
};
