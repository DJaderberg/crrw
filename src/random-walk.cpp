#include <iostream>
#include <memory>
#include "random-walk.h"
#include "node.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<Node> a(new Node());
	std::list<std::shared_ptr<Node>> bNeighbors = std::list<std::shared_ptr<Node>>();
	bNeighbors.push_back(a);
	std::shared_ptr<Node> b(new Node(bNeighbors));
	return 0;
}


