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
    graphics.init();
    graphics.nodesMinMax(set);
    
	int j = 0;
    for (int i = 0; i < 5000; ++i) {
		set.takeStep(0.1);
		std::vector<unsigned int> numPart = set.numberOfParticles();
		if (i % 5 == 0) {
			std::cout << "Iteration: " << i << "\n";
			std::stringstream imgFilename("img/a", std::ios_base::in|std::ios_base::out);
			imgFilename << "img/a";
			imgFilename << std::setfill('0') << std::setw(5) << j++ << ".png";
			std::string imgFilenameStr = imgFilename.str();
            graphics.drawEdges(set, 0);
            graphics.drawNodes(set, 0);
			graphics.writeToFile(imgFilenameStr);
            graphics.repaint();
		}
	}
	std::vector<unsigned int> numPart = set.numberOfParticles();
	
    for (auto val : numPart) {
		std::cout << val << ", ";
	}
	std::cout << "\n";
    
    return 0;
}
