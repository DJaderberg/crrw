/** @file sink.cpp
 * Contains definitions of functions in the Sink class.
 */
#include "sink.h"

void Sink::takeStep(double dt) {
	Node::takeStep(dt); //TODO: Is this necessary?
	this->numberOfParticles = 0;
}
