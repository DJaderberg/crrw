/** @file node.cpp
 * Contains definitions of functions in NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#include "nodeSetGraphics.h"
#include <stdio.h>
#include <stdlib.h>


void NodeSetGraphics::writeToFile(PositionedNodeSet n, std::string filename) {
    
    /// Size configurations in px
    unsigned int windowHeight = 800;
    unsigned int windowWidth = 1024;
    unsigned int nodeRadius = 2;
    unsigned int stdLineWidth = 1;
    
    Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, windowWidth, windowHeight);
    
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
    
    cr->save(); // save the state of the context
    //cr->set_source_rgb(0.86, 0.85, 0.47); // Greenish color
    cr->set_source_rgb(1, 01, 0.95); // Warm white color
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
    
    /*
    cr->arc(surface->get_width() / 4.0, surface->get_height() / 4.0,nodeRadius,0,2.0*M_PI);
    cr->stroke();
    
    */
    
    
    // Find min and max coordinates
    double minX, maxX, minY, maxY;
    std::array<double, 2> pos = n.getNodes().front()->getPosition();
    minX = pos[0];
    minY = pos[1];
    
    maxX = minX;
    maxY = minY;
    
    std::cout << "minX:" << minX << " minY:" << minY << " maxX:" << maxX << " maxY:" << maxY << "\n";
    
    double temp;
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        temp = pos[0];
        if (temp < minX) {
            minX = temp;
        } else if (temp > maxX) {
            maxX = temp;
        }
        temp = pos[1];
        if (temp < minY) {
            minY = temp;
        } else if (temp > maxY) {
            maxY = temp;
        }
    }
    
    std::cout << "minX:" << minX << " minY:" << minY << " maxX:" << maxX << " maxY:" << maxY << "\n";
    
    // TODO: draw the edges + handel the one dim case
    // Draw lines
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        cr->save();
        cr->arc((pos[0] - minX)/maxX*(double)windowWidth, (pos[1] - minY)/maxY*(double)windowHeight,nodeRadius,0,2.0*M_PI);
        cr->stroke();
        for (auto neighbor: node->getNeighbors()) {
            cr->move_to((pos[0] - minX)/maxX*windowWidth, (pos[1] - minY)/maxY*windowHeight);
            cr->set_line_width(node->getMeanFlow(neighbor.first));
            std::cout << node->getMeanFlow(neighbor.first);
            cr->line_to((dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[0] - minX)/maxX*(double)windowWidth, (dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[1] - minY)/maxY*(double)windowHeight);
            cr->stroke();
        }
        cr->restore();
    }
    
    surface->write_to_png(filename);
    std::cout << "Wrote png file \"" << filename << "\"" << std::endl;
}

