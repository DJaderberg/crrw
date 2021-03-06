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
    unsigned long long windowHeight;
    unsigned long long windowWidth;
    unsigned long long borderWidth;
    double nodeMinRadius;
    double nodeMaxRadius;
    double nodeBorder;
    double sourceRadius;
    double sinkRadius;
    double lineWidthMin;
    double lineWidthMax;
    double lineOpacMin;
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

void NodeSetGraphics::NAndFlowCondMinMax(PositionedNodeSet n) {
    
    long long tempN = n.getNodes().front()->getNumberOfParticles();
    double tempFlow = std::abs(n.getNodes().front()->getMeanFlow(n.getNodes().front()->getNeighborsMap().begin()->second->getId()));
    double tempCond = std::abs(n.getNodes().front()->getConductivity(n.getNodes().front()->getNeighborsMap().begin()->second->getId()));
    flowMin = flowMax = tempFlow;
    condMin = condMax = tempCond;
    
    for (auto node: n.getNodes()) {
        tempN = node->getNumberOfParticles();
        if (tempN < Nmin) {
            Nmin = tempN;
        } else if (tempN > Nmax) {
            Nmax = tempN;
        }
        
        for (auto neighbor: node->getNeighborsMap()) {
            tempFlow = std::abs(node->getMeanFlow(neighbor.second->getId()));
            if (tempFlow < flowMin) {
                flowMin = tempFlow;
            } else if (tempFlow > flowMax) {
                flowMax = tempFlow;
            }
            
            tempCond = node->getConductivity(neighbor.second->getId());
            if (tempCond < condMin) {
                condMin = tempCond;
            } else if (tempCond > condMax) {
                condMax = tempCond;
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
            //cr->set_source_rgb(0.7, 0.7, 0.7);
            cr->set_source_rgb(0, 0, 0);
            //cr->set_source_rgb(1, 1, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            cr->set_source_rgb(1, 0.2, 0.3);
            //cr->set_source_rgb(0.3, 0.6, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r,0,2.0*M_PI);
        } else if (dynamic_cast<PositionedSink<2>*>(node.get())) {
            //std::cout << "SINK\n";
            //cr->set_source_rgb(0.7, 0.7, 0.7);
            cr->set_source_rgb(0, 0, 0);
            //cr->set_source_rgb(1, 1, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            //cr->set_source_rgb(0.4, 0.4, 1);
            cr->set_source_rgb(0.4, 1, 0);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r,0,2.0*M_PI);
        } else {
            cr->set_source_rgb(0.8, 0.8, 0.8);
            //cr->set_source_rgb(0, 0, 0);
            //cr->set_source_rgb(1, 1, 1);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r + nodeBorder,0,2.0*M_PI);
            cr->stroke();
            //cr->set_source_rgb(0.2, 0.9, 0.7);
            cr->set_source_rgb(0.4, 0.4, 0.4);
            cr->arc((pos[0] - Xmin)/(Xmax - Xmin)*(double)(windowWidth-2*borderWidth) + borderWidth, (pos[1] - Ymin)/(Ymax - Ymin)*(double)(windowHeight-2*borderWidth) + borderWidth,r,0,2.0*M_PI);
        }
        cr->stroke_preserve();
        cr->fill();
        cr->set_source_rgb(0, 0, 0);
    }
    cr->restore();
}

void NodeSetGraphics::drawShortestPath(PositionedNodeSet n, std::vector<unsigned long long> sinkId, std::unordered_map<unsigned long long, long long> pathMap) {
    cr->save();
    // Draw lines
    struct lineSettings l;
    for (auto id: sinkId) {
        while (pathMap[id] != -1) {
            l.r = 0;
            l.g = 0;
            l.b = 0;
            l.alpha = 1;
            l.lineWidth = 2*lineWidthNoFlow;
            drawEdge(n.getNodes()[id], n.getNodes()[pathMap[id]], l);
            id = pathMap[id];
        }
    }
    cr->restore();
}

std::vector<unsigned long long> NodeSetGraphics::findSources(PositionedNodeSet n) {
    std::vector<unsigned long long> sourcesId;
    
    for (auto s: n.getNodes()) {
        if (std::dynamic_pointer_cast<PositionedSource<2>>(s)) {
            sourcesId.push_back(s->getId());
        }
    }
    return sourcesId;
}

std::vector<unsigned long long> NodeSetGraphics::findSinks(PositionedNodeSet n) {
    std::vector<unsigned long long> sinksId;
    
    for (auto s: n.getNodes()) {
        if (std::dynamic_pointer_cast<PositionedSink<2>>(s)) {
            sinksId.push_back(s->getId());
        }
    }
    return sinksId;
}

void NodeSetGraphics::drawEdgesFlow(PositionedNodeSet n, bool changeFlow) {
    cr->save();
    double flowMin = this->flowMin;
    double flowMax = this->flowMax;
    double flow;
    // Find min and max Mean Flow
    if (changeFlow) {
        flowMin = std::abs(n.getNodes().front()->getMeanFlow(n.getNodes().front()->getNeighbors().begin()->first));
        flowMax = flowMin;
        for (auto node: n.getNodes()) {
            for (auto neighbor: node->getNeighbors()) {
                flow = std::abs(node->getMeanFlow(neighbor.first));
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
            flow = std::abs(node->getMeanFlow(neighbor.first));
            // in no flow set different color for edge
            if (flow <= flowMax*0.005) { // flowMax*0.0005
                l.r = 0.85;
                l.g = 0.85;
                l.b = 0.85;
                l.alpha = 1;
                l.lineWidth = lineWidthNoFlow;
            } else {
                l.r = 1;
                l.g = 0.5;
                l.b = 0.1;
                l.alpha = ((flow - flowMin)/(flowMax - flowMin))*(1 - lineOpacMin) + lineOpacMin;
                l.lineWidth = ((flow - flowMin)/(flowMax-flowMin))*(lineWidthMax - lineWidthMin) + lineWidthMin;
            }
            
            drawEdge(node, std::dynamic_pointer_cast<PositionedNode<2>>(neighbor.second), l);
        }
    }
    cr->restore();
}

void NodeSetGraphics::drawEdgesCond(PositionedNodeSet n, bool changeFlow) {
    cr->save();
    double condMin = this->condMin;
    double condMax = this->condMax;
    double cond;
    // Find min and max Mean Flow
    if (changeFlow) {
        condMin = std::abs(n.getNodes().front()->getConductivity(n.getNodes().front()->getNeighbors().begin()->first));
        condMax = condMin;
        for (auto node: n.getNodes()) {
            for (auto neighbor: node->getNeighbors()) {
                cond = std::abs(node->getConductivity(neighbor.first));
                if ( cond < condMin) {
                    condMin = cond;
                } else if (cond > condMax) {
                    condMax = cond;
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
            cond = std::abs(node->getConductivity(neighbor.first));
            // in no flow set different color for edge
            if (cond <= condMax*0.005) { // flowMax*0.0005
                l.r = 0.85;
                l.g = 0.85;
                l.b = 0.85;
                l.alpha = 1;
                l.lineWidth = lineWidthNoFlow;
            } else {
                l.r = 0.5;
                l.g = 0.6;
                l.b = 1;
                l.alpha = ((cond - condMin)/(condMax - condMin))*(1 - lineOpacMin) + lineOpacMin;
                l.lineWidth = ((cond - condMin)/(condMax-condMin))*(lineWidthMax - lineWidthMin) + lineWidthMin;
            }
            
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
    cr->set_source_rgb(1, 1, 1); // White color
    //cr->set_source_rgb(0.55, 0.55, 0.55); // Blackish
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
    this->drawEdgesFlow(n, 1);
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
    
    str += "Minimum cond.: " + std::to_string(condMin) + "\n";
    str += "Maximum cond.: " + std::to_string(condMax) + "\n";
    
    str += "Surface height: " + std::to_string(windowHeight) + "\n";
    str += "Surface width: " + std::to_string(windowWidth) + "\n";
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






