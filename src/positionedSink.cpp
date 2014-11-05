/** @file positionedSink.cpp
 * Contains function declarations for the PositionedSink class
 */
#include "positionedSink.h"

template<int dimension>
void PositionedSink<dimension>::takeStep(double dt) {
	Node::takeStep(dt); //TODO: Is this necessary?
	this->numberOfParticles = 0;
}
