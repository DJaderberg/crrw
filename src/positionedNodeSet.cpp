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
/*
void PositionedNodeSet::parseTGF(std::istream& input, std::shared_ptr<Element> e) {
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int number, productionRate;
		double x, y;
		//If we can extract an int, create a new Node
		if (iss >> number >> x >> y) {
			std::array<double, 2> pos;
			pos[0] = x;
			pos[1] = y;
			//If we can get another int, it could be a Source or a sink
			if (iss >> productionRate) {
				if (productionRate > 0) {
					std::shared_ptr<PositionedSource<2>> tempNode(new PositionedSource<2>(e, pos, productionRate));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				} else if (productionRate < 0) {
					std::shared_ptr<PositionedSink<2>> tempNode(new PositionedSink<2>(e, pos));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				} else {
					std::shared_ptr<PositionedNode<2>> tempNode(new PositionedNode<2>(e, pos));
					this->positionedNodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				}
			} else {
				std::shared_ptr<PositionedNode<2>> tempNode(new PositionedNode<2>(e, pos));
				this->positionedNodes.push_back(tempNode);
				idMap[number] = tempNode->getId();
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
			positionedNodes[idMap[from]]->insertNeighbor(positionedNodes[idMap[to]]);
		}
	}
}*/

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
	for (auto node : positionedNodes) {
		node->prepareStep(dt);
	}
	for (auto node : positionedNodes) {
		node->takeStep(dt);
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
