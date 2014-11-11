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
    
    std::ofstream ofs("saved.txt");

    for (int i = 0; i < 30; ++i) {
		set.takeStep(0.1);
		std::vector<unsigned int> numPart = set.numberOfParticles();
        std::cout << "Iteration: " << i << "\n";
        set.writeNumPartToStream(ofs);
	}
    
    ofs.close();
    
    std::shared_ptr<AntElement> e2(new AntElement());
    algorithmCreator create2 = CurrentWalk::create;
    PositionedNodeSet set2 = PositionedNodeSet("test/nodes2d.txt", create2, e2);
    std::cout << set2.toString();
    
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