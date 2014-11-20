/** @file generateData.cpp
 * Function for generating data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#include "generateData.h"
#include "omp.h"
#include <string>
#include <fstream>

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, bool force) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    if (!force && exists(dataSavePath)) {
        std::cout << "ERROR in GeneratData: save file already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
    
    std::string dataSavePathLast = dataSavePath;
    int pos = dataSavePathLast.find_last_of('.');
    dataSavePathLast.insert(pos,"LAST");
    
    if (!force && exists(dataSavePathLast)) {
        std::cout << "ERROR in GeneratData: save file \"LAST\" already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
    
    std::ofstream ofs(dataSavePath);
    
    for (int i = 0; i < nCount; ++i) {
        set.takeStep(dt);
        if (i % writeInterval == 0) {
            set.writeData(ofs);
            ofs << "\n";
        }
        if (i % 1000 == 0) {
            std::cout << "Iter: " << std::to_string(i) << "\n";
        }
    }
    ofs.close();
    
    std::ofstream ofsLast(dataSavePathLast);
    set.writeData(ofsLast);
    ofsLast.close();
}


/**
 * Function for generating data, starting from dataReadPath
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, bool force, std::string dataReadPath) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);

    if (!force && exists(dataSavePath)) {
        std::cout << "ERROR in GeneratData: save file already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
	
	std::string dataSavePathLast = dataSavePath;
    int pos = dataSavePathLast.find_last_of('.');
    dataSavePathLast.insert(pos,"LAST");
    
    if (!force && exists(dataSavePathLast)) {
        std::cout << "ERROR in GeneratData: save file \"LAST\" already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }

    std::ifstream ifs(dataReadPath);
    set.readData(ifs);
    ifs.close();
    std::ofstream ofs(dataSavePath);
    
    for (int i = 0; i < nCount; ++i) {
        set.takeStep(dt);
        if (i % writeInterval == 0) {
            set.writeData(ofs);
            ofs << "\n";
        }
        if (i % 1000 == 0) {
            std::cout << "Iter: " << std::to_string(i) << "\n";
        }
    }
    ofs.close();
    
    std::ofstream ofsLast(dataSavePathLast);
    set.writeData(ofsLast);
    ofsLast.close();
}








