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
class PositionedSource : public PositionedNode<dimension> {
public:
	/**
	 * Create a PositionedSource
	 *
	 * @param pos The position of the Source
	 * @param p The production rate of the Source
	 */
	PositionedSource(std::array<double, dimension> pos, int p) : PositionedNode<dimension>(pos), productionRate(p) {
	};
	///Return the id of the Source
	unsigned int getId() {
		return ((PositionedNode<dimension> *) this)->getId();
	};
	/**
     * Get the production rate of this Source
     *
     * @return How many elements are produced by this Source during one time unit
     */
    int getProductionRate() {
		return this->productionRate;
	}
	virtual std::string toString() {
		std::string prod = "Production rate: " + std::to_string(this->productionRate) + "\n";
		return PositionedNode<dimension>::toString() + prod;
	}
private:
    /**
     * The production rate of the Source
     *
     * Any source with a negative production rate can be considered as
     * a sink.
     */
    int productionRate = 0;
	///Random number generation state
	std::random_device rd;

};
