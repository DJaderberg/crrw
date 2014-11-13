/** @file generateData.cpp
 * Function for generating data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#include "generateData.h"
#include <string>
#include <fstream>

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<AntElement> e, algorithmCreator create, int nCount, double dt, int writeInterval) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    std::ofstream ofs(dataSavePath);
    
    for (int i = 0; i < nCount; ++i) {
        set.takeStep(dt);
        if (i % writeInterval == 0) {
            set.writeData(ofs);
            ofs << "\n";
        }
    }
    
    ofs.close();
    
}










