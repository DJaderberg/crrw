#include "random-walk.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes.txt";
	NodeSet set = NodeSet(filename, e);
	std::cout << set.toString();
	for (int i = 0; i < 10000; ++i) {
		set.takeStep(0.01);
	}
	std::vector<unsigned int> numPart = set.numberOfParticles();
	for (auto val : numPart) {
		std::cout << val << ", ";
	}
	std::cout << "\n";
    return 0;
}
