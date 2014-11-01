#include "random-walk.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<AntElement> e(new AntElement());
	std::shared_ptr<Node> a(new Node(e));
	std::list<std::shared_ptr<Node>> bNeighbors = std::list<std::shared_ptr<Node>>();
	std::list<double> bDistances = {1};
	bNeighbors.push_back(a);
	std::shared_ptr<Node> b(new Node(bNeighbors, bDistances, e));
	return 0;
}

