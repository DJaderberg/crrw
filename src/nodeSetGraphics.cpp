/** @file node.cpp
 * Contains definitions of functions in NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#include "nodeSetGraphics.h"
#include <stdio.h>
#include <stdlib.h>


void NodeSetGraphics::writeToFile(NodeSet n, std::string filename) {
    
    /// Size configurations in px
    unsigned int windowHeight = 800;
    unsigned int windowWidth = 1024;
    unsigned int nodeRadius = 2;
    unsigned int stdLineWidth = 1;
    
    Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, windowWidth, windowHeight);
    
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
    
    cr->save(); // save the state of the context
    cr->set_source_rgb(0.86, 0.85, 0.47);
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
    
    cr->arc(surface->get_width() / 4.0, surface->get_height() / 4.0,nodeRadius,0,2.0*M_PI);
    cr->stroke();
    
    /*
    // Find min and max coordinates
    int minX, maxX, minY, maxY;
    
    minX = NodeSet.getNodes().front().getX();
    minY = NodeSet.getNodes().front().getY();
    
    maxX = minX;
    maxY = minY;
    
    for (auto node: NodeSet.getNodes()) {
        double temp = node.getX();
        if (temp < minX) {
            minX = temp;
        } else if (temp > maxX) {
            maxX = temp;
        }
        double temp = node.getY();
        if (temp < minY) {
            minY = temp;
        } else if (temp > maxY) {
            maxY = temp;
        }
    }
    */
    
    /*
     // Draw lines
     for (auto node: NodeSet.getNodes()) {
        cr->arc(surface->get_width() / 4.0, surface->get_height() / 4.0,nodeRadius,0,2.0*M_PI);
        cr->stroke();
        for (auto neighbor: node.getNeighborsMap()) {
            cr->move_to((node.getX() - minX)/maxX*windowWidth, (node.getY() - minY)/maxY*windowHeight);
            cr->line_to((neighbor.getX() - minX)/maxX*windowWidth, (neighbor.getY() - minY)/maxY*windowHeight);
            cr->stroke();
        }
     }
     */
    for (int i = 0; i < 1; i++) {
        
        cr->line_to(surface->get_width() * 3.0 / 4.0, surface->get_height() * 3.0 / 4.0);
        cr->stroke();
    }
    
    /*
     cr->save();
     // draw a border around the image
     cr->set_line_width(20.0); // make the line wider
     cr->rectangle(0.0, 0.0, surface->get_width(), surface->get_height());
     cr->stroke();
     
     cr->set_source_rgba(0.0, 0.0, 0.0, 0.7);
     // draw a circle in the center of the image
     cr->arc(surface->get_width() / 2.0, surface->get_height() / 2.0, surface->get_height() / 4.0, 0.0, 2.0 * M_PI);
     cr->stroke();
     
     // draw a diagonal line
     cr->move_to(surface->get_width() / 4.0, surface->get_height() / 4.0);
     cr->line_to(surface->get_width() * 3.0 / 4.0, surface->get_height() * 3.0 / 4.0);
     cr->stroke();
     cr->restore();
     
     */
    
    surface->write_to_png(filename);
    
    std::cout << "Wrote png file \"" << filename << "\"" << std::endl;
}

