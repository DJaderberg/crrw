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
#include <stdlib.h>

/**
 * Core function for generating data
 */
void generateDataCore(PositionedNodeSet set, std::string dataSavePath, int nCount, double dt, int writeInterval, bool force) {
    
    if (!force && exists(dataSavePath)) {
        std::cout << "ERROR in GenerateData: save file already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
    
    std::string dataSavePathLast = dataSavePath;
    int pos = dataSavePathLast.find_last_of('.');
    dataSavePathLast.insert(pos,"_LAST");
    
    if (!force && exists(dataSavePathLast)) {
        std::cout << "ERROR in GeneratData: save file \"LAST\" already exists.\n";
        std::cout << "Data generation aborted.\n";
        return;
    }
    
    std::ofstream ofs(dataSavePath);
    double time = omp_get_wtime();
    
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
    
    
    time = omp_get_wtime() - time;
    std::cout << "Execution time: " << time << "\n";
    ofs.close();
    
    std::ofstream ofsLast(dataSavePathLast);
    set.writeData(ofsLast);
    ofsLast.close();
}

/**
 * Function for writing info to stream
 *
 */
void writeInfo(PositionedNodeSet set, std::string dataSavePath, std::shared_ptr<Element> e, int nCount, double dt, int writeInterval, bool force) {
    std::string dataInfoPath = dataSavePath;
    int pos = dataInfoPath.find_last_of('.');
    dataInfoPath.insert(pos,"_INFO");
    
    if (!force && exists(dataInfoPath)) {
        std::cout << "ERROR in GeneratData: save file \"INFO\" already exists.\n";
        std::cout << "Info writing aborted.\n";
        return;
    }
    
    std::ofstream ofsInfo(dataInfoPath);
    
    ofsInfo << "GENERAL INFO\n";
    ofsInfo << "dt: " << dt << "\n";
    ofsInfo << "nCount: " << nCount << "\n";
    ofsInfo << "writeInterval: " << writeInterval << "\n";
    ofsInfo << "Computation length: " << nCount*dt << "\n";
    ofsInfo << "Number of threads: " << omp_get_max_threads() << "\n";
    
    ofsInfo << "\nELEMENT INFO\n" << e->toString();
    
    ofsInfo << "\nNODE SET INFO\n";
    ofsInfo << "Number of nodes: " << set.getNodes().size() << "\n";
    
    ofsInfo.close();
}

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, bool force) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    writeInfo(set, dataSavePath, e, nCount, dt, writeInterval, force);
    
    generateDataCore(set, dataSavePath, nCount, dt, writeInterval, force);
}


/**
 * Function for generating data, starting from dataReadPath
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, bool force, std::string dataReadPath) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    std::ifstream ifs(dataReadPath);
    set.readData(ifs);
    ifs.close();

    writeInfo(set, dataSavePath, e, nCount, dt, writeInterval, force);
    
    generateDataCore(set, dataSavePath, nCount, dt, writeInterval, force);
}








