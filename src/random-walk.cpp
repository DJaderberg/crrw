#include <iostream>
#include "random-walk.h"
#include "node.h"

int main() {
	std::cout << "Hello World!\n";
	Node* a = new Node();
	std::list<Node*> bNeighbors = std::list<Node*>();
	bNeighbors.push_back(a);
	Node* b = new Node(bNeighbors);
	return 0;
}


