/** @file node.cpp
 * Contains definitions of functions in NodeSetGraphics.
 */
//
//  Created by Kristoffer Jonsson on 04/11/14.
//

#ifdef GRAPHICS
#include "nodeSetGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

struct defaultValues {
    // Parameters for keeping track of the coordinates and flows
    double flowMin = 0;
    double flowMax = 100;
    double Nmin = 0;
    double Nmax = 200;
};

struct parametersValues {
    // Size configurations in px
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

struct lineSettings {
    double r;
    double g;
    double b;
    double alpha;
    double lineWidth;
};

void NodeSetGraphics::init() {
    defaultValues d;
    // Default values flows and number of particles
    flowMin = d.flowMin;
    flowMax = d.flowMax;
    Nmin = d.Nmin;
    Nmax = d.Nmax;
    
    this->reset();
    this->repaint();
}

void NodeSetGraphics::init(struct parametersValues p) {
    defaultValues d;
    // Default values flows and number of particles
    flowMin = d.flowMin;
    flowMax = d.flowMax;
    Nmin = d.Nmin;
    Nmax = d.Nmax;
    
    // Size configurations in px
    windowHeight = p.windowHeight;
    windowWidth = p.windowWidth;
    borderWidth = p.borderWidth;
    nodeMinRadius = p.nodeMinRadius;
    nodeMaxRadius = p.nodeMaxRadius;
    nodeBorder = p.nodeBorder;
    sourceRadius = p.sourceRadius;
    sinkRadius = p.sinkRadius;
    lineWidthMin = p.lineWidthMin;
    lineWidthMax = p.lineWidthMax;
    lineOpacMin = p.lineOpacMin;
    
    this->reset();
    this->repaint();
}

void NodeSetGraphics::XYMinMax(PositionedNodeSet n) {
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
}

void NodeSetGraphics::NAndFlowMinMax(PositionedNodeSet n) {
    
    int tempN = n.getNodes().front()->getNumberOfParticles();
    double tempFlow = abs(n.getNodes().front()->getMeanFlow(n.getNodes().front()->getNeighborsMap().begin()->second->getId()));
    
    for (auto node: n.getNodes()) {
        tempN = node->getNumberOfParticles();
        if (tempN < Nmin) {
            Nmin = tempN;
        } else if (tempN > Nmax) {
            Nmax = tempN;
        }
        
        for (auto neighbor: node->getNeighborsMap()) {
            tempFlow = abs(node->getMeanFlow(neighbor.second->getId()));
            if (tempFlow < flowMin) {
                flowMin = tempFlow;
            } else if (tempFlow > flowMax) {
                flowMax = tempFlow;
            }
        }
    }
    
}


void NodeSetGraphics::drawNodes(PositionedNodeSet n, bool changeSize) {
    cr->save();
    double Nmin = this->Nmin;
    double Nmax = this->Nmax;
    double N;
    // Find min and max NumberOfParticles
    if (changeSize) {
        Nmin = n.getNodes().front()->getNumberOfParticles();
        Nmax = Nmin;
        for (auto node: n.getNodes()) {
            N = node->getNumberOfParticles();
            if ( N < Nmin) {
                Nmin = N;
            } else if (N > Nmax) {
                Nmax = N;
            }
        }
    }
    
    //std::cout << "Nmin:" << Nmin << " Nmax:" << Nmax << "\n";
    
    std::array<double, 2> pos;
    double r;
    // Draw the nodes on top of the edges
    
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        N = node->getNumberOfParticles();
        r = sqrt((N - Nmin)/(Nmax-Nmin))*(nodeMaxRadius - nodeMinRadius) + nodeMinRadius;
        //std::cout << "N:" << N << " r:" << r << "\n";
        // Determine if the node is a Source, Sink or an ordinary Node
        if (dynamic_cast<PositionedSource<2>*>(node.get())) {
            //std::cout << "SOURCE\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sourceRadius + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(1, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sourceRadius,0,2.0*M_PI);
        } else if (dynamic_cast<PositionedSink<2>*>(node.get())) {
            //std::cout << "SINK\n";
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sinkRadius + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.4, 0.4, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,sinkRadius,0,2.0*M_PI);
        } else {
            cr->set_source_rgb(0, 0, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(0.2, 0.9, 0.7);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r,0,2.0*M_PI);
        }
        cr->stroke_preserve();
        cr->fill();
        cr->set_source_rgb(0, 0, 0);
    }
    cr->restore();
}

std::unordered_map<unsigned int, int> NodeSetGraphics::findShortestPath(PositionedNodeSet n, unsigned int sourceId) {
    std::unordered_map<unsigned int, int> pathMap = n.shortestPath(sourceId).second;
    return pathMap;
}

std::vector<unsigned int> NodeSetGraphics::findSources(PositionedNodeSet n) {
    std::vector<unsigned int> sources;
    
    for (auto s: n.getNodes()) {
        auto temp = std::dynamic_pointer_cast<PositionedSource<2>>(s);
        if (1) {
            std::cout << temp;
            sources.back() = s->getId();
        }
        //std::cout << s->toString();
    }
    return sources;
}

void NodeSetGraphics::drawEdges(PositionedNodeSet n, bool changeFlow) {
    cr->save();
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
    
    // TODO:handle the one dim case
    // Draw lines
    std::array<double, 2> pos;
    for (auto node: n.getNodes()) {
        pos =node->getPosition();
        
        for (auto neighbor: node->getNeighbors()) {
            struct lineSettings l;
            flow = abs(node->getMeanFlow(neighbor.first));
            // in no flow set different color for edge
            if (flow == 0) {
                l.r = 1;
                l.g = 0;
                l.b = 1;
                l.alpha = 1;
            } else {
                l.r = 0.2;
                l.g = 0.2;
                l.b = 0.2;
                l.alpha = ((flow - flowMin)/(flowMax - flowMin))*(1 - lineOpacMin) + lineOpacMin;
            }
            
            l.lineWidth = ((flow - flowMin)/(flowMax-flowMin))*(lineWidthMax - lineWidthMin) + lineWidthMin;
            drawEdge(node, std::dynamic_pointer_cast<PositionedNode<2>>(neighbor.second), l);
        }
    }
    cr->restore();
}

void NodeSetGraphics::drawEdge(std::shared_ptr<PositionedNode<2>> node, std::shared_ptr<PositionedNode<2>> neighbor, struct lineSettings l) {
    cr->save();
    std::array<double, 2> pos =node->getPosition();
    cr->move_to((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
    
    cr->set_source_rgba(l.r, l.g, l.b, l.alpha);

    cr->set_line_width(l.lineWidth);
    cr->line_to((neighbor->getPosition()[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (neighbor->getPosition()[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth);
    cr->stroke();
    cr->restore();
}

void NodeSetGraphics::setDefaultValues(struct defaultValues d) {
    flowMin = d.flowMin;
    flowMax = d.flowMax;
    Nmin = d.Nmin;
    Nmax = d.Nmax;
}

void NodeSetGraphics::setParmeters(struct parametersValues p) {
    windowHeight = p.windowHeight;
    windowWidth = p.windowWidth;
    borderWidth = p.borderWidth;
    nodeMinRadius = p.nodeMinRadius;
    nodeMaxRadius = p.nodeMaxRadius;
    nodeBorder = p.nodeBorder;
    sourceRadius = p.sourceRadius;
    sinkRadius = p.sinkRadius;
    lineWidthMin = p.lineWidthMin;
    lineWidthMax = p.lineWidthMax;
    lineOpacMin = p.lineOpacMin;
}

void NodeSetGraphics::repaint() {
    cr->save(); // save the state of the context
    //cr->set_source_rgb(0.86, 0.85, 0.47); // Greenish color
    cr->set_source_rgb(1, 1, 0.97); // Warm white color
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now
}

void NodeSetGraphics::reset() {
    surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, windowWidth, windowHeight);
    cr = Cairo::Context::create(surface);
}

void NodeSetGraphics::writeToFile(std::string filename) {
     surface->write_to_png(filename);
}

void NodeSetGraphics::writeToFile(PositionedNodeSet n, std::string filename) {
    this->init();
    this->XYMinMax(n);
    this->drawEdges(n, 1);
    this->drawNodes(n, 1);
    this->writeToFile(filename);
}

std::string NodeSetGraphics::toString() {
    std::string str;
    
    str = "Minimum X-coord: " + std::to_string(Xmin) + "\n";
    str += "Maximum X-coord: " + std::to_string(Xmax) + "\n";
    str += "Minimum Y-coord: " + std::to_string(Ymin) + "\n";
    str += "Maximum Y-coord: " + std::to_string(Ymax) + "\n";
    
    str += "Minimum Num. part.: " + std::to_string(Nmin) + "\n";
    str += "Maximum Num. part.: " + std::to_string(Nmax) + "\n";
    
    str += "Minimum flow: " + std::to_string(flowMin) + "\n";
    str += "Maximum flow: " + std::to_string(flowMax) + "\n";
    
    str += "Surface height: " + std::to_string(windowHeight) + "\n";
    str += "Surface width: " + std::to_string(windowWidth) + "\n";
    str += "Border width: " + std::to_string(borderWidth) + "\n";
    str += "Border width: " + std::to_string(borderWidth) + "\n";
    str += "Minimum Node radius: " + std::to_string(nodeMinRadius) + "\n";
    str += "Maximum Node radius: " + std::to_string(nodeMaxRadius) + "\n";
    str += "Minimum Node radius: " + std::to_string(nodeMinRadius) + "\n";
    str += "Node border size: " + std::to_string(nodeBorder) + "\n";
    str += "Source radius: " + std::to_string(sourceRadius) + "\n";
    str += "Sink radius: " + std::to_string(sinkRadius) + "\n";
    str += "Minimum line width: " + std::to_string(lineWidthMin) + "\n";
    str += "Maximum line width: " + std::to_string(lineWidthMax) + "\n";
    str += "Minimum line opacity: " + std::to_string(lineOpacMin) + "\n";
    
    return str;
}

#endif






