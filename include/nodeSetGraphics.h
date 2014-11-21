/** @file nodeSetGraphics.h
 * Contains declarations of NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#pragma once
#ifdef GRAPHICS
#include "positionedNodeSet.h"
#include "positionedSource.h"
#include "positionedSink.h"
#include <string>
#include <iostream>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <cmath>
#include <typeinfo>

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
    void init(struct parametersValues p);
    
    /**
     * Finds the minimum and maximum x- and y-coordinates
     *
     * @param a PositionedNodeSet
     */
    void XYMinMax(PositionedNodeSet n);
    
    /**
     * Finds the minimum and maximum number of particles and flows
     *
     * @param a PositionedNodeSet
     */
    void NAndFlowMinMax(PositionedNodeSet n);
    
    /**
     * Draws all the Nodes in the NodeSet n to cr
     *
     * @param a NodeSet
     * @param boolean to tell if the node size should be statically drawn or of it should be normalized in every frame.
     */
    void drawNodes(PositionedNodeSet n, bool changeSize);
    
    /**
     * Finds the shortest path map for a PositionedNodeSet and a source
     *
     * @param n A PositionedNodeSet
     * @param sourceId An id for the starting poit, i.e the node from which to calculate the shortest paths
     * @return an unordered map of the shortest path from the scorce, im-memory id is the key.
     */
    std::unordered_map<unsigned int, int> findShortestPath(PositionedNodeSet n, unsigned int sourceId);
    
    /**
     * Finds the Sources in a PositionedNodeSet
     *
     * @param n A PositionedNodeSet
     * @return a vector with the ids of the sources in the set
     */
    std::vector<unsigned int> findSources(PositionedNodeSet n);
    /**
     * Draws all the edges in the NodeSet n to cr
     *
     * @param a NodeSet
     * @param boolean to tell if the flow should be statically drawn or of it should be normalized in every frame.
     */
    void drawEdges(PositionedNodeSet n, bool changeFlow);
    
    /**
     * Draws all the edges in the NodeSet n to cr
     *
     * @param node Node to start drawing from
     * @param neighbor A neighbor to the node
     * @param struct lineSettings A struct with line colors, opacity and line width.
     */
    void drawEdge(std::shared_ptr<PositionedNode<2>> node, std::shared_ptr<PositionedNode<2>> neighbor, struct lineSettings l);
    
    /**
     * Sets the default values for X and Y coord. along with min and max flow to those stored in the sturct d
     *
     * @param d A struct of the default values
     */
    void setDefaultValues(struct defaultValues d);
    
    /**
     * Sets the parameters to those stored in the sturct p
     *
     * @param p A struct of the parameter
     */
    void setParmeters(struct parametersValues p);
    
    /**
     * Repaints the surface to its original empty state
     *
     */
    void repaint();
    
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
    
    /** Return a string representation of the NodeSetGraphics parameters and min and max values
     *
     * @return std::string
     *
     */
    std::string toString();
    
private:
    /// The active Cairomm context
    Cairo::RefPtr<Cairo::Context> cr;
    /// The active Cairomm surface that the images are beeing drawn upon.
    Cairo::RefPtr<Cairo::ImageSurface> surface;
    /// Help parameters for keeping track of the coordinates and flows
    double Xmin, Xmax, Ymin, Ymax, flowMin, flowMax, Nmin, Nmax;
    
    /// Size configurations in px
    unsigned int windowHeight = 800;
    unsigned int windowWidth = 1024;
    unsigned int borderWidth = 100;
    double nodeMinRadius = 1;
    double nodeMaxRadius = 10;
    double nodeBorder = 2;
    double sourceRadius = 10;
    double sinkRadius = 10;
    double lineWidthMin = 1;
    double lineWidthMax = 30;
    double lineOpacMin = 1;
    
};
#endif
