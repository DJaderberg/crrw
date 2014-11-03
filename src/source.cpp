#include "source.h"

int Source::getProductionRate() {
	return this->productionRate;
}

void Source::takeStep() {
	this->numberOfParticles += this->productionRate;
	Node::takeStep();
}
