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
    
#ifdef GRAPHICS
    NodeSetGraphics graphics = NodeSetGraphics();
    graphics.init();
    graphics.nodesMinMax(set);
#endif
    
    std::ofstream ofs("data/save.txt");
    
    int nCount = 10000;
    for (int i = 0; i < nCount; ++i) {
        if (i % 100 == 0) {
            std::cout << "CalcIter: " << i << "\n";
        }
        set.takeStep(0.1);
        set.writeData(ofs);
        ofs << "\n";
        
    }
    
    ofs.close();
    
#ifdef GRAPHICS
    set = PositionedNodeSet("test/nodes2d.txt", create, e);
    
    std::ifstream ifs("data/save.txt");
    
    int j = 0;
    for (int i = 0; i < nCount; i++) {
        set.readData(ifs);
        if (i % 5 == 0) {
            set.reinitialize();
            std::cout << "GraphicsIter: " << i << "\n";
            std::stringstream imgFilename("img/a", std::ios_base::in|std::ios_base::out);
            imgFilename << "img/a";
            imgFilename << std::setfill('0') << std::setw(5) << j++ << ".png";
            std::string imgFilenameStr = imgFilename.str();
            graphics.drawEdges(set, 1);
            graphics.drawNodes(set, 1);
            graphics.writeToFile(imgFilenameStr);
            graphics.repaint();
        }
    }
    
    ifs.close();
#endif
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
