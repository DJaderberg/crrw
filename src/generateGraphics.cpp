/** @file generateGraphics.cpp
 * Function for generating images from data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#ifdef GRAPHICS
#include "generateGraphics.h"
#include <string>
#include <fstream>

/**
 * Function for generating images from data
 */
void generateGraphics(std::string nodePath, std::string dataReadPath, std::string imageSavePath, std::shared_ptr<AntElement> e, algorithmCreator create, int nCount, int writeInterval) {
    
    NodeSetGraphics graphics = NodeSetGraphics();
    graphics.init();
    
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    std::ifstream ifs(dataReadPath);
    
    int j = 0;
    for (int i = 0; i < nCount; i++) {
        set.readData(ifs);
        if (i % writeInterval == 0) {
            set.reinitialize();
            std::stringstream imgFilename(imageSavePath, std::ios_base::in|std::ios_base::out);
            imgFilename << imageSavePath;
            imgFilename << std::setfill('0') << std::setw(6) << j++ << ".png";
            std::string imgFilenameStr = imgFilename.str();
            graphics.drawEdges(set, 1);
            graphics.drawNodes(set, 1);
            graphics.writeToFile(imgFilenameStr);
            graphics.repaint();
        }
    }
    
    ifs.close();
    
}
#endif