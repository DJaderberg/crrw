
#include "reduceNodes.h"
#include <memory>
#include <typeinfo>

std::shared_ptr<PositionedNodeSet> reduceNodes(std::shared_ptr<PositionedNodeSet> old, double distance) {
	std::shared_ptr<PositionedNodeSet> ret(new PositionedNodeSet());
	auto oldNodes = old->getNodes();
	std::unordered_map<unsigned int, unsigned int> oldIdToOldVecPos;
	std::unordered_map<unsigned int, unsigned int> newIdToNewVecPos;
	int i = 0;
	for (auto node : oldNodes) {
		oldIdToOldVecPos[node->getId()] = i++;
	}
	std::unordered_map<unsigned int, unsigned int> oldToNew;
	std::unordered_map<unsigned int, std::vector<unsigned int>> newToOld;
	i = 0;
	//Create new nodes where necessary
	for (auto oldNode : oldNodes) {
		auto newNodes = ret->getNodes();
		bool matchFound = false;
		for (auto node : newNodes) {
			if (!matchFound && node->distance(oldNode) < distance) {
				matchFound = true;
				//Add mappings
				oldToNew[oldNode->getId()] = node->getId();
				newToOld[node->getId()].push_back(oldNode->getId());
				break;
			}
		}
		//If no match found, create a new node in the new set
		if (!matchFound) {
			auto node =new PositionedNode<2>(oldNode->getPosition());
			ret->addNode(std::shared_ptr<PositionedNode<2>>(node));
			node->setFileId(i);
			oldToNew[oldNode->getId()] = node->getId();
			newToOld[node->getId()].push_back(oldNode->getId());
			newIdToNewVecPos[node->getId()] = i;
			i++;
		}
	}
	
	//TODO: Change this so that the outermost loop is over all old nodes.
	//		This should help reduce the number of loops necessary and hopefully
	//		allow this to be done without memory access errors.
	//Create neighbor-ness between the new nodes
	auto newNodes = ret->getNodes();
	for (auto oldNode : oldNodes) {
		unsigned int newId = oldToNew[oldNode->getId()];
		for (auto oldNeighbor : oldNode->getNeighbors()) {
			unsigned int newNeighborId = oldToNew[oldNeighbor.first];
			newNodes[newIdToNewVecPos[newId]]->insertNeighborUnique(newNodes[newIdToNewVecPos[newNeighborId]]);
		}
	}
	/*
	auto newNodes = ret->getNodes();
	for (auto node : newNodes) {
		for (auto oldId : newToOld[node->getId()]) {
			auto oldNode = oldNodes[oldIdToOldVecPos[oldId]];
			auto oldNeighbors = oldNode->getNeighbors();
			for (auto oldNeighbor : oldNeighbors) {
				unsigned int newNeighborId = oldToNew[oldNeighbor.first];
				auto newNeighbor = newNodes[newNeighborId];
				std:: cout << "My id: " << node->getId() << "\tNew neighbor id: " << newNeighborId << "\tOld: " << oldNeighbor.first << "\n";
				//std::cout << "Current node: " << node->getId() << "\tNeighbor ids: New:" << oldToNew[oldNeighbor.first] << "\tOld: " << oldNeighbor.first << "\n";
				if (auto positionedNeighbor = std::dynamic_pointer_cast<PositionedNode<2>>(newNeighbor)) {
					std::cout << "Pos:d neighbor id: " << positionedNeighbor->getId() << "\n";
					node->insertNeighborUnique(positionedNeighbor);
				}
			}
		}
	}
	*/
	return ret;
}
