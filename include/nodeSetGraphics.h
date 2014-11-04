/** @file nodeSetGraphics.h
 * Contains declarations of NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#pragma once
#include "nodeSet.h"

class NodeSetGraphics {
public:
    
    /**
     * Create a new NodeSetGraphics object.
     */
    NodeSetGraphics();
    
    /**
     * Draws all the connections and nodes the NodeSet n
     *
     * @param a NodeSet
     */
    void draw(NodeSet n);
    
private:
    /** GLUT display callback function.  Every time the window needs to be drawn,
     glut will call this function.  This includes when the window size
     changes, or when another window covering part of this window is
     moved so this window is uncovered.
     */
    void display(void);
    
    /** GLUT reshape callback function.  GLUT calls this function whenever
     the window is resized, including the first time it is created.
     You can use variables to keep track the current window size.
     */
    void reshape(int, int);
    
};