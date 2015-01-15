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
		long long number, productionRate;
		//If we can extract an long long, create a new Node
		if (iss >> number) {
			//If we can get another long long, it could be a Source or a drain
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
		long long from, to;
		double distance;
		if (iss >> from >> to >> distance) {
			nodes[idMap[from]]->insertNeighbor(nodes[idMap[to]], distance);
		}
	}
}

std::string NodeSet::toString() {
	std::string ret = "";
	ret += "Partitioning: ";
	for(auto part : partitioning) {
		ret += std::to_string(part) + ", ";
	}
	ret += "\n";
	for (auto node : nodes) {
		ret += node->toString();
	}
	return ret;
}

std::vector<unsigned long long> NodeSet::numberOfParticles() {
	std::vector<unsigned long long> ret = std::vector<unsigned long long>();
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

long long NodeSet::partition(long long partition) {
	return this->partitioning[partition];
}

long long NodeSet::partitionSize() {
	return this->partitioning.size() ? this->partitioning.size() - 1 : 0;
}

