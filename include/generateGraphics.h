//
//  generateGraphics.h
//  Random_Walk
//
//  Created by Kristoffer Jonsson on 13/11/14.
//

#pragma once
#include <iostream>
#include <iomanip>
#include <memory>
#include "positionedNodeSet.h"
#include "source.h"
#include "antElement.h"
#include "currentWalk.h"
#include "randomWalk.h"
#include "nodeSetGraphics.h"
#include "positionedNodeSet.h"

/**
 * Function for generating images from data
 */
void generateGraphics(std::string nodePath, std::string dataReadPath, std::string imageSavePath, std::shared_ptr<AntElement> e, algorithmCreator create, int nCount, int writeInterval);