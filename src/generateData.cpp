/** @file generateData.cpp
 * Function for generating data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#pragma once
#include "generateData.h"
#include <string>
#include <fstream>
#include <sys/stat.h>

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    if (exists(dataSavePath)) {
        std::cout << "ERROR in GeneratData: save file already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
    
    std::string dataSavePathLast = dataSavePath;
    int pos = dataSavePathLast.find_last_of('.');
    dataSavePathLast.insert(pos,"LAST");
    
    if (exists(dataSavePathLast)) {
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
    }
    ofs.close();
    
    std::ofstream ofsLast(dataSavePathLast);
    set.writeData(ofsLast);
    ofsLast.close();
}


/**
 * Function for generating data, starting from dataReadPath
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, std::string dataReadPath) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
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
    }
    ofs.close();
    
}

inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}








