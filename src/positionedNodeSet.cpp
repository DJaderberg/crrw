/** @file positionedNodeSet.cpp
 * Contains definitions of functions in the class PositionedNodeSet.
 */
#include "positionedNodeSet.h"
#include "positionedSource.h"
#include "positionedSink.h"
#include <sstream>
#include <unordered_map>
#include <string>
#include <memory>
#ifndef GRAPHICS
#include <omp.h>
#endif

//TODO: Make this throw exceptions when file is incorrectly formatted
void PositionedNodeSet::parseTGF(std::istream& input) {
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		long long number, productionRate;
		double x, y;
		//If we can extract an long long and two doubles, create a new Node
		if (iss >> number >> x >> y) {
			std::array<double, 2> pos;
			pos[0] = x;
			pos[1] = y;
			//If we can get another long long, it could be a Source or a sink
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
		long long from, to;
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

std::vector<unsigned long long> PositionedNodeSet::numberOfParticles() {
	std::vector<unsigned long long> ret = std::vector<unsigned long long>();
	ret.reserve(positionedNodes.size()); //Alloc space for as many elements as are in nodes
	for (auto n : positionedNodes) {
		ret.push_back(n->getNumberOfParticles());
	}
	return ret;
}

void PositionedNodeSet::takeStep(double dt) {
	unsigned int size = algorithms.size();
	auto algoBegin = algorithms.begin();
	auto algo = algoBegin;
#pragma omp parallel
    {
#pragma omp for private(algo)
	for (unsigned int i = 0; i < size; i++) {
		algo = algoBegin + i;
		(*algo)->prepareStep(dt);
	}
#pragma omp for private(algo)
	for (unsigned int i = 0; i < size; i++) {
		algo = algoBegin + i;
		(*algo)->takeStep(dt);
	}
    }
}

void PositionedNodeSet::reinitialize() {
	for (auto algo : algorithms) {
		algo->reinitialize();
	}
}

std::unordered_map<unsigned long long, std::array<double, 2>> PositionedNodeSet::getPositions() {
	std::unordered_map<unsigned long long, std::array<double, 2>> positions;
	for (auto n : positionedNodes) {
		positions[n->getId()] = n->getPosition();
	}
	return positions;
}

std::vector<std::shared_ptr<PositionedNode<2>>> PositionedNodeSet::getNodes() {
	return positionedNodes;
}

std::pair<std::unordered_map<unsigned long long, double>, std::unordered_map<unsigned long long, long long>> PositionedNodeSet::shortestPath(unsigned long long source) {
	std::unordered_map<unsigned long long, double> distances;
	std::unordered_map<unsigned long long, long long> previous;
	std::unordered_map<unsigned long long, std::shared_ptr<PositionedNode<2>>> Q;
	for (auto n : this->positionedNodes) {
		Q[n->getId()] = n;
		distances[n->getId()] = 1e20;
		previous[n->getId()] = -1;
	}
	distances[source] = 0;
	unsigned long long u = source;
	bool first = true;
	while (Q.size() > 0) {
		//std::cout << "Q.size(): " << Q.size() << "\n";
		//std::cout << "u: " << u << "\n";
		//Find nearest neighbor to u and choose that neighbor as the new u
		if (first) {
			u = source;
			first = false;
		} else {
			double curMin = 1e21;
			unsigned long long uTemp;
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
	std::pair<std::unordered_map<unsigned long long, double>, std::unordered_map<unsigned long long, long long>> ret(distances, previous);
	return ret;
}

void PositionedNodeSet::writeMETIS(std::ostream& stream) {
	//Stream to which all connections are buffered
	std::stringstream connection;
	//Count number of edges (divide by 2 in the end)
	unsigned long long numEdges = 0;
	stream << positionedNodes.size() << " ";
	//For each node, write all neighbors (separated by space)
	for (auto p : positionedNodes) {
		for (auto n : p->getNeighborsMap()) {
			connection << n.first+1 << " ";
			++numEdges;
		}
		connection << "\n";
	}
	stream << numEdges/2 << "\n";
	stream << connection.rdbuf();
}

void PositionedNodeSet::readMETIS(std::istream& input, std::ostream& output, unsigned long long numPart) {
	std::string line;
	std::vector<std::vector<unsigned long long>> partVectors;

	//Calculate shortest paths - which are to be used for finding which nodes are connected to the large network
	auto pair = shortestPath(0);
	auto distances = pair.first;
	//Initialize vectors
	for (unsigned long long i = 0; i < numPart; i++) {
		partVectors.push_back(std::vector<unsigned long long>());
	}
	//Add all nodes to the correct partition by reading the value in the METIS file
	for (auto n : positionedNodes) {
		std::getline(input, line);
		long long part = std::stoi(line);
		partVectors[part].push_back(n->getId());
	}
	//output << positionedNodes.size() << '\n';
	std::unordered_map<unsigned long long, unsigned long long> oldToNewId;
	//Add all nodes to the output, in order of partitions
	unsigned long long id = 0;
	for (auto v : partVectors) {
		for (auto n : v) {
			//Don't add this node if it isn't connected to the network
			if (distances[n] < 1e19) {
				oldToNewId[n] = id;
				output << id << ' '; //Print id
				++id;
				//Print position
				auto posArray = positionedNodes[n]->getPosition();
				for (auto pos : posArray) {
					output << pos << ' ';
				}
				if (auto source = std::dynamic_pointer_cast<PositionedSource<posArray.size()>>(positionedNodes[n])) {
					output << source->getProductionRate();
				} else if (auto sink = std::dynamic_pointer_cast<PositionedSink<posArray.size()>>(positionedNodes[n])) {
					output << sink->getRemovalRate();
				}
				output << '\n';
			}
		}
	}
	output << "#\n";
	//Print all edges to the output, correctly renamed
	for (auto n : positionedNodes) {
		unsigned long long id = oldToNewId[n->getId()];
		//Don't add this node if it isn't connected to the network
		if (distances[n->getId()] < 1e19) {
			for (auto neighbor : n->getNeighbors()) {
				unsigned long long neighborId = oldToNewId[neighbor.first];
				output << id << ' ' << neighborId << '\n';
			}
		}
	}
}

void PositionedNodeSet::writeTGF(std::ostream& output) {
	//Write down all nodes
	for (auto n : positionedNodes) {
		auto pos = n->getPosition();
		output << n->getFileId() << ' ' << pos[0] << ' ' << pos[1] << '\n';
	}
	output << "#\n";
	for (auto n : positionedNodes) {
		for (auto neighbor : n->getNeighbors()) {
			output << n->getFileId() << ' ' << neighbor.second->getFileId() << '\n';
		}
	}
}

