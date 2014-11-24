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
void generateGraphics(std::string nodePath, std::string dataReadPath, std::string imageSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, int writeInterval, bool force) {
    
    NodeSetGraphics graphics = NodeSetGraphics();
    graphics.init();
    
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    graphics.XYMinMax(set);
    
    std::vector<unsigned int> sourceId = graphics.findSources(set);
    std::vector<unsigned int> sinkId = graphics.findSinks(set);
    
    std::vector<std::unordered_map<unsigned int, int>> pathMaps;
    
    for (auto id: sourceId) {
        pathMaps.push_back(set.shortestPath(id).second);
    }
    
    std::ifstream ifsMinMx(dataReadPath);
    std::cout << "Finding min and max...\n";
    
    
    for (int i = 0; i < nCount; i++) {
        set.readData(ifsMinMx);
        graphics.NAndFlowMinMax(set);
    }
    
    ifsMinMx.close();
    
    std::cout << graphics.toString();
    
    std::ifstream ifs(dataReadPath);
    
    int j = 0;
	if (!force) {
		while (true) {
			std::stringstream imgFilename(imageSavePath, std::ios_base::in|std::ios_base::out);
			imgFilename << imageSavePath;
			imgFilename << std::setfill('0') << std::setw(6) << j << ".png";
			std::string imgFilenameStr = imgFilename.str();
			if (!exists(imgFilenameStr)) {
				break;
			} else {
				j++;
			}
		}
	}

	if (j != 0) {
		std::cout << "Found existing images, creating new images starting at number " << j << "\n";
	}
    
    std::cout << "Image generation begun.\n";
    std::string loadBar = "";
    
    for (int i = 0; i < nCount; i++) {
        if (i % writeInterval == 0) {
            set.readData(ifs);
            set.reinitialize();
            std::stringstream imgFilename(imageSavePath, std::ios_base::in|std::ios_base::out);
            imgFilename << imageSavePath;
            imgFilename << std::setfill('0') << std::setw(6) << j++ << ".png";
            std::string imgFilenameStr = imgFilename.str();
            graphics.drawEdges(set, 0);
            
            for (auto pathMap: pathMaps) {
                graphics.drawShortestPath(set, sinkId, pathMap);
            }

            graphics.drawNodes(set, 0);
            graphics.writeToFile(imgFilenameStr);
            graphics.repaint();
        } else {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        // Printing loadbar
        if (nCount >= 100) {
            if (i % (nCount/50) == 0) {
                loadBar += '#';
                std::cout << "\r" << loadBar << "..."  << 100*i/nCount << "%";
                std::cout.flush();
            }
            if (i % (nCount/100) == 0) {
                std::cout << "\r" << loadBar << "..."  << 100*i/nCount << "%";
                std::cout.flush();
            }
        }
    }
    
    if (nCount >= 100) {
        loadBar += '#';
        std::cout << "\r" << loadBar << "..."  << "100%\n";
        std::cout.flush();
    }
    
    ifs.close();
    
    
}
#endif
