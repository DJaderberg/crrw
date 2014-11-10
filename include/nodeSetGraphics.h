/** @file nodeSetGraphics.h
 * Contains declarations of NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#pragma once
#include "positionedNodeSet.h"
#include "positionedSource.h"
#include "positionedSink.h"
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
     * Initialize surface and cr
     *
     */
    void init();
    
    /**
     * Initialize surface and cr plus setting parameter values according to the struct p
     * @param a struct the has information about the graphics 
     */
    void init(struct parameters p);
    
    /**
     * Finds the minimum and maximum x- and y-coordinates
     *
     * @param a NodeSet
     */
    void nodesMinMax(PositionedNodeSet n);
    
    /**
     * Draws all the Nodes in the NodeSet n to cr
     *
     * @param a NodeSet
     * @param boolean to tell if the node size should be statically drawn or of it should be normalized in every frame.
     */
    void drawNodes(PositionedNodeSet n, bool changeSize);
    
    /**
     * Draws all the edges in the NodeSet n to cr
     *
     * @param a NodeSet
     * @param boolean to tell if the flow should be statically drawn or of it should be normalized in every frame.
     */
    void drawEdges(PositionedNodeSet n, bool changeFlow);
    
    /**
     * Resets the surface and cr to its original empty state
     *
     */
    void reset();
    
    /**
     * Writes cr to file
     *
     * @param the name of the file
     */
    void writeToFile(std::string filename);
    
    /**
     * Draws all the connections and nodes the NodeSet n and writes to file
     *
     * @param a NodeSet
     * @param the name of the file
     */
    void writeToFile(PositionedNodeSet n, std::string filename);
    
private:
    /// The active Cairomm surface that the images are beeing drawn upon.
    Cairo::RefPtr<Cairo::ImageSurface> surface;
    /// The active Cairomm context
    Cairo::RefPtr<Cairo::Context> cr;
    
    /// Help parameters for keeping track of the coordinates and flows
    double Xmin, Xmax, Ymin, Ymax, flowMin, flowMax, Nmin, Nmax;
    
    /// Size configurations in px
    unsigned int windowHeight = 800;
    unsigned int windowWidth = 1024;
    unsigned int borderWidth = 100;
    double nodeMinRadius = 1;
    double nodeMaxRadius = 10;
    double nodeBorder = 2;
    double sourceRadius = 4;
    double sinkRadius = 4;
    double lineWidthMin = 1;
    double lineWidthMax = 80;
    double lineOpacMin = 1;
    
};