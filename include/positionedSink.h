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
	PositionedSink(std::array<double, dimension> pos, int r) : PositionedNode<dimension>(pos), removalRate(r) {
	};
	///Return the id of the Sink
	unsigned int getId() {
		return ((PositionedNode<dimension> *) this)->getId();
	};
    int getRemovalRate() {
        return this->removalRate;
    }
	//Return string representation of the Sink
	std::string toString() {
		return PositionedNode<dimension>::toString() + "Sink\n";
	}
private:
    /**
     * The production rate of the Source
     *
     * Any source with a negative production rate can be considered as
     * a sink.
     */
    int removalRate = 0;
    ///Random number generation state
    std::random_device rd;
};
