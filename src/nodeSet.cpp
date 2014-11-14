/** @file nodeSet.cpp
 * Contains definitions of functions in the class NodeSet.
 */
//
//  Created by Kristoffer Jonsson on 03/11/14.
//
#include "nodeSet.h"
#include "source.h"
#include "sink.h"
#include <sstream>
#include <unordered_map>
#include <string>

//TODO: Make this throw exceptions when file is incorrectly formatted
void NodeSet::parseTGF(std::istream& input) {
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int number, productionRate;
		//If we can extract an int, create a new Node
		if (iss >> number) {
			//If we can get another int, it could be a Source or a drain
			if (iss >> productionRate) {
				if (productionRate > 0) {
					std::shared_ptr<Source> tempNode(new Source(productionRate));
					this->nodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				} else if (productionRate < 0) {
					std::shared_ptr<Sink> tempNode(new Sink());
					this->nodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				} else {
					std::shared_ptr<Node> tempNode(new Node());
					this->nodes.push_back(tempNode);
					idMap[number] = tempNode->getId();
				}
			} else {
				std::shared_ptr<Node> tempNode(new Node());
				this->nodes.push_back(tempNode);
				idMap[number] = tempNode->getId();
			}
		// Otherwise we are done with creating Nodes
		} else {
			break;
		}
	}
	nodes.shrink_to_fit(); //This won't grow any more
	//The next step is to set up all the connections
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		int from, to;
		double distance;
		if (iss >> from >> to >> distance) {
			nodes[idMap[from]]->insertNeighbor(nodes[idMap[to]], distance);
		}
	}
}

std::string NodeSet::toString() {
	std::string ret = "";
	for (auto node : nodes) {
		ret += node->toString();
	}
	return ret;
}

std::vector<unsigned int> NodeSet::numberOfParticles() {
	std::vector<unsigned int> ret = std::vector<unsigned int>();
	ret.reserve(nodes.size()); //Alloc space for as many elements as are in nodes
	for (auto n : nodes) {
		ret.push_back(n->getNumberOfParticles());
	}
	return ret;
}

void NodeSet::takeStep(double dt) {
	for (auto algo : algorithms) {
		algo->prepareStep(dt);
	}
	for (auto algo : algorithms) {
		algo->takeStep(dt);
	}
}
