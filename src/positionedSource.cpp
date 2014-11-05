/** @file positionedSource.cpp
 * Contains function declarations for the PositionedSource class
 */
#include "positionedSource.h"
template<int dimension>
std::string PositionedSource<dimension>::toString() {
	std::string prod = "Production rate: " + std::to_string(this->productionRate) + "\n";
	return PositionedNode<dimension>::toString() + prod;
}

template<int dimension>
int PositionedSource<dimension>::getProductionRate() {
	return this->productionRate;
}

template<int dimension>
void PositionedSource<dimension>::takeStep(double dt) {
	std::poisson_distribution<int> rngDist(productionRate*dt);
	double randomValue = rngDist(rd);
	this->numberOfParticles += randomValue;
	Node::takeStep(dt);
}
