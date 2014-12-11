#include "source.h"

long long Source::getProductionRate() {
	return this->productionRate;
}

std::string Source::toString() {
	std::string prod = "Production rate: " + std::to_string(this->productionRate) + "\n";
	return Node::toString() + prod;
}

