#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>

int main() {
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes.txt";
	algorithmCreator create = CurrentWalk::create;
	PositionedNodeSet set = PositionedNodeSet(filename, create, e);
    std::cout << set.toString();
    
    NodeSetGraphics graphics = NodeSetGraphics();
    graphics.init();
    graphics.nodesMinMax(set);
    
    std::ofstream ofs("NumPart.txt");

    for (int i = 0; i < 10; ++i) {
		set.takeStep(0.1);
		std::vector<unsigned int> numPart = set.numberOfParticles();
        std::cout << "Iteration: " << i << "\n";
        set.writeData(ofs);
        ofs << "\n";
        
	}
    
    ofs.close();
    
    set = PositionedNodeSet("test/nodes.txt", create, e);
    //std::cout << set.toString();
    
    std::ifstream ifs("NumPart.txt");
    
    for (int i = 0; i < 10; i++) {
        set.readData(ifs);
    }
    graphics.writeToFile(set, "image.png");

    std::cout << set.toString();
    
    //graphics.writeToFile(set, "image.png");
    
    return 0;
}



/*
 NodeSetGraphics graphics = NodeSetGraphics();
 graphics.init();
 graphics.nodesMinMax(set);
 */

/*
 if (i % 5 == 0) {
 //std::cout << "Iteration: " << i << "\n";
 std::stringstream imgFilename("img/a", std::ios_base::in|std::ios_base::out);
 imgFilename << "img/a";
 imgFilename << std::setfill('0') << std::setw(5) << j++ << ".png";
 std::string imgFilenameStr = imgFilename.str();
 graphics.drawEdges(set, 1);
 graphics.drawNodes(set, 1);
 graphics.writeToFile(imgFilenameStr);
 graphics.repaint();
 
 }
 */