/** @file generateData.cpp
 * Function for generating data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#include "generateData.h"
#include <string>
#include <fstream>
#include <stdlib.h>

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, bool force) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);

    if (!force && exists(dataSavePath)) {
        std::cout << "ERROR in GenerateData: save file already exists.\n";
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
    
    std::string loadBar = "";
    
    for (int i = 0; i < nCount; ++i) {
        set.takeStep(dt);
        if (i % writeInterval == 0) {
            set.writeData(ofs);
            ofs << "\n";
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
    
    std::string loadBar = "";
    
    for (int i = 0; i < nCount; ++i) {
        set.takeStep(dt);
        if (i % writeInterval == 0) {
            set.writeData(ofs);
            ofs << "\n";
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
    
    ofs.close();
    
    std::ofstream ofsLast(dataSavePathLast);
    set.writeData(ofsLast);
    ofsLast.close();
}








