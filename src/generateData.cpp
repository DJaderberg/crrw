/** @file generateData.cpp
 * Function for generating data
 */
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#include "generateData.h"
#include <string>
#include <fstream>
#include <omp.h>

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval) {
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
    
    std::ofstream ofs(dataSavePath);
    
#pragma omp parallel
{
	std::cout << "Hello from thread: " << omp_get_thread_num() << "\n";
    for (int i = 0; i < nCount; ++i) {
#pragma omp single
{
		if (i % 1000 == 0) {
			std::cout << "Iteration: " << i << "\n";
		}
        set.takeStep(dt);
}
        if (i % writeInterval == 0) {
#pragma omp critical
{
            set.writeData(ofs);
            ofs << "\n";
}
        }
    }
}
    ofs.close();
    
    std::string dataSavePathLast = dataSavePath;
    int pos = dataSavePathLast.find_last_of('.');
    dataSavePathLast.insert(pos,"LAST");
    
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
    
#pragma omp parallel
    {
        for (int i = 0; i < nCount; ++i) {
#pragma omp single
            {
                set.takeStep(dt);
                if (i % writeInterval == 0) {
                    set.writeData(ofs);
                    ofs << "\n";
                }
            }
        }
    }
    ofs.close();
    
}









