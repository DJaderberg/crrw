#include "random-walk.h"

int main() {
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes.txt";
	algorithmCreator create = CurrentWalk::create;
	PositionedNodeSet set = PositionedNodeSet(filename, create, e);
	std::cout << set.toString();
    NodeSetGraphics graphics = NodeSetGraphics();
    
    for (int i = 0; i < 10000; ++i) {
		set.takeStep(0.1);
		std::vector<unsigned int> numPart = set.numberOfParticles();
	}
	std::vector<unsigned int> numPart = set.numberOfParticles();
	
    for (auto val : numPart) {
		std::cout << val << ", ";
	}
	std::cout << "\n";
    
    graphics.writeToFile(set, "image.png");
    
    return 0;
}
