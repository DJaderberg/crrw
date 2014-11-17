//
//  generateData.h
//  Random_Walk
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#pragma once
#include <iostream>
#include <memory>
#include "positionedNodeSet.h"
#include "source.h"
#include "antElement.h"
#include "currentWalk.h"
#include "randomWalk.h"
#include "positionedNodeSet.h"

/**
 * Function for generating data
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval);

/**
 * Function for generating data, starting from dataReadPath
 */
void generateData(std::string nodePath, std::string dataSavePath, std::shared_ptr<Element> e, algorithmCreator create, int nCount, double dt, int writeInterval, std::string dataReadPath);

/**
 *
 *
 */
bool exists(const std::string& name);