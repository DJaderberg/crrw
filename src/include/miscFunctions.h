//
//  miscFunctions.h
//  Random_Walk
//
//  Created by Kristoffer Jonsson on 19/11/14.

#pragma once
#include <sys/stat.h>

/** Checks if a file exist
 *
 * @return a bool, true if the file exists.
 */
inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}