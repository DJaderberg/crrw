/** @file node.cpp
 * Contains definitions of functions in NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#include "nodeSetGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

struct parameters {
    /// Parameters for keeping track of the coordinates and flows
    double flowMin = 0;
    double flowMax = 70;
    
    /// Size configurations in px
    unsigned int windowHeight = 800;
    unsigned int windowWidth = 1024;
    unsigned int borderWidth = 100;
    double nodeRadius = 2;
    double sourceRadius = 4;
    double sinkRadius = 4;
    double lineWidthMin = 1;
    double lineWidthMax = 80;
    double lineOpacMin = 0.5;
};

void NodeSetGraphics::init() {
    surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, windowWidth, windowHeight);
    cr = Cairo::Context::create(surface);
    
    cr->save(); // save the state of the context
    //cr->set_source_rgb(0.86, 0.85, 0.47); // Greenish color
    cr->set_source_rgb(1, 1, 0.97); // Warm white color
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
}

void NodeSetGraphics::init(struct parameters p) {
    
    // Parameters for keeping track of the coordinates and flows
    flowMin = p.flowMin;
    flowMax = p.flowMax;
    
    // Size configurations in px
    windowHeight = p.windowHeight;
    windowWidth = p.windowWidth;
    borderWidth = p.borderWidth;
    nodeRadius = p.nodeRadius;
    sourceRadius = p.sourceRadius;
    sinkRadius = p.sinkRadius;
    lineWidthMin = p.lineWidthMin;
    lineWidthMax = p.lineWidthMax;
    lineOpacMin = p.lineOpacMin;
    
    cr->save(); // save the state of the context
    //cr->set_source_rgb(0.86, 0.85, 0.47); // Greenish color
    cr->set_source_rgb(1, 1, 0.97); // Warm white color
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
    
    surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, windowWidth, windowHeight);
    cr = Cairo::Context::create(surface);
}

void NodeSetGraphics::writeToFile(PositionedNodeSet n, std::string filename) {
    cr->save(); // save the state of the context
    //cr->set_source_rgb(0.86, 0.85, 0.47); // Greenish color
    cr->set_source_rgb(1, 1, 0.97); // Warm white color
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
    
    // Find min and max coordinates
    double Xmin, Xmax, Ymin, Ymax, flowMin, flowMax;
    std::array<double, 2> pos = n.getNodes().front()->getPosition();
    Xmin = pos[0];
    Ymin = pos[1];
    Xmax = Xmin;
    Ymax = Ymin;
    
    //std::cout << "Xmin:" << Xmin << " Ymin:" << Ymin << " Xmax:" << Xmax << " Ymax:" << Ymax << "\n";
    
    double temp;
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        temp = pos[0];
        if (temp < Xmin) {
            Xmin = temp;
        } else if (temp > Xmax) {
            Xmax = temp;
        }
        temp = pos[1];
        if (temp < Ymin) {
            Ymin = temp;
        } else if (temp > Ymax) {
            Ymax = temp;
        }
    }
    
    //std::cout << "Xmin:" << Xmin << " Ymin:" << Ymin << " Xmax:" << Xmax << " Ymax:" << Ymax << "\n";
    
    double flow;
    // Find min and max Mean Flow
    flowMin = abs(n.getNodes().front()->getMeanFlow(n.getNodes().front()->getNeighbors().begin()->first));
    flowMax = flowMin;
    
    
    for (auto node: n.getNodes()) {
        for (auto neighbor: node->getNeighbors()) {
            flow = abs(node->getMeanFlow(neighbor.first));
            if ( flow < flowMin) {
                flowMin = flow;
            } else if (flow > flowMax) {
                flowMax = flow;
            }
        }
    }
    
    //std::cout << "flowMin:" << flowMin << " flowMax:" << flowMax << "\n";
    
    // TODO:handle the one dim case
    // Draw lines
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        cr->save();
        for (auto neighbor: node->getNeighbors()) {
            cr->move_to((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
            flow = abs(node->getMeanFlow(neighbor.first));
            // in no flow set different color for edge
            if (flow == 0) {
                cr->set_source_rgba(1, 0, 1, 1);
            } else {
                cr->set_source_rgba(0.2, 0.2, 0.2, ((flow - flowMin)/(flowMax - flowMin))*(1 - lineOpacMin) + lineOpacMin);
            }
            
            cr->set_line_width(((flow - flowMin)/(flowMax-flowMin))*(lineWidthMax - lineWidthMin) + lineWidthMin);
            //cr->set_line_width(1);
            //std::cout << node->getMeanFlow(neighbor.first) << "\n";
            cr->line_to((dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
            cr->stroke();
        }
        cr->restore();
    }
    
    // Draw the nodes on top of the edges
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        
        // Determine if the node is a Source, Sink or an ordinary Node
        if (dynamic_cast<PositionedSource<2>*>(node.get())) {
            //std::cout << "SOURCE\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+sourceRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(1, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sourceRadius,0,2.0*M_PI);
        } else if (dynamic_cast<PositionedSink<2>*>(node.get())) {
            //std::cout << "SINK\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+sinkRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.4, 0.4, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sinkRadius,0,2.0*M_PI);
        } else {
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+nodeRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.1, 0.9, 0.7);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,nodeRadius,0,2.0*M_PI);
        }
        cr->stroke_preserve();
        cr->fill();
        cr->set_source_rgb(0, 0, 0);
    }
    
    surface->write_to_png(filename);
    //std::cout << "Wrote png file \"" << filename << "\"" << std::endl;
}

void NodeSetGraphics::drawNodes(PositionedNodeSet n) {
    std::array<double, 2> pos = n.getNodes().front()->getPosition();
    this->Xmin = pos[0];
    this->Ymin = pos[1];
    this->Xmax = this->Xmin;
    this->Ymax = this->Ymin;
    
    //std::cout << "Xmin:" << Xmin << " Ymin:" << Ymin << " Xmax:" << Xmax << " Ymax:" << Ymax << "\n";
    
    double temp;
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        temp = pos[0];
        if (temp < Xmin) {
            Xmin = temp;
        } else if (temp > Xmax) {
            Xmax = temp;
        }
        temp = pos[1];
        if (temp < Ymin) {
            Ymin = temp;
        } else if (temp > Ymax) {
            Ymax = temp;
        }
    }
    
    // Draw the nodes on top of the edges
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        
        // Determine if the node is a Source, Sink or an ordinary Node
        if (dynamic_cast<PositionedSource<2>*>(node.get())) {
            //std::cout << "SOURCE\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+sourceRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(1, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sourceRadius,0,2.0*M_PI);
        } else if (dynamic_cast<PositionedSink<2>*>(node.get())) {
            //std::cout << "SINK\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+sinkRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.4, 0.4, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sinkRadius,0,2.0*M_PI);
        } else {
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,1+nodeRadius,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.1, 0.9, 0.7);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,nodeRadius,0,2.0*M_PI);
        }
        cr->stroke_preserve();
        cr->fill();
        cr->set_source_rgb(0, 0, 0);
    }
}

void NodeSetGraphics::drawEdges(PositionedNodeSet n, bool changeFlow) {
    double flowMin = this->flowMin;
    double flowMax = this->flowMax;
    double flow;
    // Find min and max Mean Flow
    if (changeFlow) {
        flowMin = abs(n.getNodes().front()->getMeanFlow(n.getNodes().front()->getNeighbors().begin()->first));
        flowMax = flowMin;
        for (auto node: n.getNodes()) {
            for (auto neighbor: node->getNeighbors()) {
                flow = abs(node->getMeanFlow(neighbor.first));
                if ( flow < flowMin) {
                    flowMin = flow;
                } else if (flow > flowMax) {
                    flowMax = flow;
                }
            }
        }
    }
    
    //std::cout << "flowMin:" << flowMin << " flowMax:" << flowMax << "\n";
    
    // TODO:handle the one dim case
    // Draw lines
    std::array<double, 2> pos;
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        cr->save();
        for (auto neighbor: node->getNeighbors()) {
            cr->move_to((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
            flow = abs(node->getMeanFlow(neighbor.first));
            // in no flow set different color for edge
            if (flow == 0) {
                cr->set_source_rgba(1, 0, 1, 1);
            } else {
                cr->set_source_rgba(0.2, 0.2, 0.2, ((flow - flowMin)/(flowMax - flowMin))*(1 - lineOpacMin) + lineOpacMin);
            }
            
            cr->set_line_width(((flow - flowMin)/(flowMax-flowMin))*(lineWidthMax - lineWidthMin) + lineWidthMin);
            //cr->set_line_width(1);
            //std::cout << node->getMeanFlow(neighbor.first) << "\n";
            //std::cout << ((flow - flowMin)/(flowMax-flowMin))*(lineWidthMax - lineWidthMin) + lineWidthMin << "\n";
            cr->line_to((dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (dynamic_cast<PositionedNode<2>*>(neighbor.second.get())->getPosition()[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
            cr->stroke();
        }
        cr->restore();
    }
}

void NodeSetGraphics::writeToFile(std::string filename) {
    surface->write_to_png(filename);
}








