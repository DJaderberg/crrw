/** @file storableAlgorithm.h
 * Contains declarations of StorableAlgorithm
 */
#pragma once
#include "algorithm.h"
#include <fstream>
#include <iostream>

class StorableAlgorithm : public Algorithm {
public:
	/**
	 * Fully restore state after readData()
	 *
	 * This method should always be called after readData() and its purpose is 
	 * to calculate any state that is not explicitly stored in file, such as 
	 * parameters that used when taking a step, but can be calculated from 
	 * other data that is stored in file.
	 */
	virtual void reinitialize() = 0;
    /*
     * Function for storing all the algorithms data to a stream
     *
     * @param os The stream into which to store data
     */
    virtual void writeData(std::ostream& os) = 0;
    
    /*
     * Function for storing all the algorithms data to a file
     *
     * @param filename The filename of the file into which to store data
     */
    void writeData(const std::string& filename){
        std::ofstream ofs(filename);
        writeData(ofs);
        ofs.close();
    };
    
    /*
     * Function for reading all the algorithms data from a stream
     *
     * @param is The stream from which to read data
     */
    virtual void readData(std::istream& is) = 0;
    
    /*
     * Function for reading all the algorithms data from a file
     *
     * @param filename The filename of the file from which to read data
     */
    void readData(const std::string& filename){
        std::ifstream ifs(filename);
        readData(ifs);
        ifs.close();
    };
};
