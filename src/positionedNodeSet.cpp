/** @file positionedNodeSet.cpp
 * Contains definitions of functions in the class PositionedNodeSet.
 */
#include "positionedNodeSet.h"
#include "positionedSource.h"
#include "positionedSink.h"
#include <sstream>
#include <unordered_map>
#include <string>

//TODO: Make this throw exceptions when file is incorrectly formatted
void PositionedNodeSet::parseTGF(std::istream& input) {
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int number, productionRate;
		double x, y;
		//If we can extract an int and two doubles, create a new Node
		if (iss >> number >> x >> y) {
			std::array<double, 2> pos;
			pos[0] = x;
			pos[1] = y;
			//If we can get another int, it could be a Source or a sink
			if (iss >> productionRate) {
				if (productionRate > 0) {
					std::shared_ptr<PositionedSource<2>> tempNode(new PositionedSource<2>(pos, productionRate));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
					inverseIdMap[tempNode->getId()] = number;
                    tempNode->setFileId(number);
				} else if (productionRate < 0) {
					std::shared_ptr<PositionedSink<2>> tempNode(new PositionedSink<2>(pos, productionRate));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
					inverseIdMap[tempNode->getId()] = number;
                    tempNode->setFileId(number);
				} else {
					std::shared_ptr<PositionedNode<2>> tempNode(new PositionedNode<2>(pos));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
					inverseIdMap[tempNode->getId()] = number;
                    tempNode->setFileId(number);
				}
			} else {
				std::shared_ptr<PositionedNode<2>> tempNode(new PositionedNode<2>(pos));
				this->positionedNodes.push_back(tempNode);
				idMap[number] = tempNode->getId();
				inverseIdMap[tempNode->getId()] = number;
                tempNode->setFileId(number);
			}
		// Otherwise we are done with creating Nodes
		} else {
			break;
		}
	}
	positionedNodes.shrink_to_fit(); //This won't grow any more
	//The next step is to set up all the connections
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int from, to;
		if (iss >> from >> to) {
			positionedNodes[from]->insertNeighbor(positionedNodes[to]);
		}
	}
}

std::string PositionedNodeSet::toString() {
	std::string ret = "";
	for (auto node : positionedNodes) {
		ret += node->toString();
	}
	return ret;
}

std::vector<unsigned int> PositionedNodeSet::numberOfParticles() {
	std::vector<unsigned int> ret = std::vector<unsigned int>();
	ret.reserve(positionedNodes.size()); //Alloc space for as many elements as are in nodes
	for (auto n : positionedNodes) {
		ret.push_back(n->getNumberOfParticles());
	}
	return ret;
}

void PositionedNodeSet::takeStep(double dt) {
	for (auto algo : algorithms) {
		algo->prepareStep(dt);
	}
	for (auto algo : algorithms) {
		algo->takeStep(dt);
	}
}

void PositionedNodeSet::reinitialize() {
	for (auto algo : algorithms) {
		algo->reinitialize();
	}
}

std::unordered_map<unsigned int, std::array<double, 2>> PositionedNodeSet::getPositions() {
	std::unordered_map<unsigned int, std::array<double, 2>> positions;
	for (auto n : positionedNodes) {
		positions[n->getId()] = n->getPosition();
	}
	return positions;
}

std::vector<std::shared_ptr<PositionedNode<2>>> PositionedNodeSet::getNodes() {
	return positionedNodes;
}

std::pair<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, int>> PositionedNodeSet::shortestPath(unsigned int source) {
	std::unordered_map<unsigned int, double> distances;
	std::unordered_map<unsigned int, int> previous;
	std::unordered_map<unsigned int, std::shared_ptr<PositionedNode<2>>> Q;
	for (auto n : this->positionedNodes) {
		Q[n->getId()] = n;
		distances[n->getId()] = 1e20;
		previous[n->getId()] = -1;
	}
	distances[source] = 0;
	unsigned int u = source;
	bool first = true;
	while (Q.size() > 0) {
		std::cout << "Q.size(): " << Q.size() << "\n";
		std::cout << "u: " << u << "\n";
		//Find nearest neighbor to u and choose that neighbor as the new u
		if (first) {
			u = source;
			first = false;
		} else {
			double curMin = 1e21;
			unsigned int uTemp;
			for (auto v : Q) {
				double w = distances[v.first];
				if (w < curMin) {
					curMin = w;
					uTemp = v.first;
				}
			}
			u = uTemp;
		}
		Q.erase(u);
		for (auto v : positionedNodes[u]->getNeighbors()) {
			double alt = distances[u] + v.second->getDistanceMap()[u];
			if (alt < distances[v.first]) {
				distances[v.first] = alt;
				previous[v.first] = u;
			}
		}
	}
	std::pair<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, int>> ret(distances, previous);
	return ret;
}

