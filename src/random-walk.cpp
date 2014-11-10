#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>

int main() {
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes2d.txt";
	algorithmCreator create = CurrentWalk::create;
	PositionedNodeSet set = PositionedNodeSet(filename, create, e);
	std::cout << set.toString();
    NodeSetGraphics graphics = NodeSetGraphics();
    
	int j = 0;
    for (int i = 0; i < 1000; ++i) {
		set.takeStep(0.1);
		std::vector<unsigned int> numPart = set.numberOfParticles();
		if (i % 1 == 0) {
			std::cout << "Iteration: " << i << "\n";
			std::stringstream imgFilename("img/a", std::ios_base::in|std::ios_base::out);
			imgFilename << "img/a";
			imgFilename << std::setfill('0') << std::setw(5) << j++ << ".png";
			std::string imgFilenameStr = imgFilename.str();
			graphics.writeToFile(set, imgFilenameStr);
		}
	}
	std::vector<unsigned int> numPart = set.numberOfParticles();
	
    for (auto val : numPart) {
		std::cout << val << ", ";
	}
	std::cout << "\n";
    
    graphics.writeToFile(set, "image.png");
    
    return 0;
}
