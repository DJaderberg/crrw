/** @file nodeSetGraphics.h
 * Contains declarations of NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#pragma once
#include "nodeSet.h"
#include <string>
#include <iostream>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <cmath>

class NodeSetGraphics {
public:
    
    /**
     * Create a new NodeSetGraphics object.
     */
    NodeSetGraphics() {};
    
    /**
     * Draws all the connections and nodes the NodeSet n
     *
     * @param a NodeSet
     * @param the name of the file
     */
    void writeToFile(NodeSet n, std::string filename);
    
    
private:
};