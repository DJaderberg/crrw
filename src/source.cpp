#include "source.h"

int Source::getProductionRate() {
	return this->productionRate;
}

void Source::takeStep(double dt) {
	this->numberOfParticles += this->productionRate;
	Node::takeStep(dt);
}

std::string Source::toString() {
	std::string prod = "Production rate: " + std::to_string(this->productionRate) + "\n";
	return Node::toString() + prod;
}

