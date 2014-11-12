/** @file currentWalk.h
 * Contains declarations of CurrentWalk
 */
#pragma once
#include <memory>
#include "storableAlgorithm.h"
#include "antElement.h"
#include "positionedSource.h"
#include "positionedSink.h"
#include <fstream>
#include <iostream>
#include <sstream>

class CurrentWalkSource;
class CurrentWalkSink;

class CurrentWalk : public StorableAlgorithm {
public:
    void prepareStep(double dt);
    void takeStep(double dt);
    virtual void initialize(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
        this->element = element;
        this->node = n;
        for (auto i : n->getNeighbors()) {
            conductivityMap[i.second->getId()] = element->Dmin;
        }
    }
    
    /** Write all data to stream
     *
     * @param os Stream to write to
     */
    void writeData(std::ostream& os) {
        writeNumPart(os);
        writeConductivityMap(os);
    }
    
    /** Read all data from stream
     *
     * @param is Stream to read from
     */
    void readData(std::istream& is) {
        readNumPart(is);
        readConductivityMap(is);
    }
    
    /**
     * Create a CurrentWalk object that is initialized with n and element.
     *
     * @param n The Node to initialize the CurrentWalk with
     * @param element The Element to initialize the Node with
     */
    static std::shared_ptr<Algorithm> create(std::shared_ptr<Node> n, std::shared_ptr<Element> element);
    virtual ~CurrentWalk() {}
protected:
    /** Helper function for writing number of particles to stream
     *
     * @param os Stream to write to
     */
    void writeNumPart(std::ostream& os)
    {
        os << node->getNumberOfParticles() << ';';
    }
    
    /** Helper function for reading number of particles from stream
     *
     * @param is Stream to read from
     */
    void readNumPart(std::istream& is)
    {
        unsigned int temp;
        char separator;
        is >> temp >> separator;
        if (separator != ';') {
            std::cout << "ERROR in CurrentWalk, readNumPart(): incorrect separator " << separator << ", should be (;)\n";
        }
        node->setNumberOfParticles(temp);
    }
    
    /** Helper function for writing conductivityMap to stream
     *
     * @param os Stream to write to
     * @param func Function for getting the file id from the in memory id
     */
    void writeConductivityMap(std::ostream& os)
    {
        // first write the fileId then write the corresponding conductivity.
        for (auto n: conductivityMap) {
            os << node->getNeighborsMap()[n.first]->getFileId() << " " << n.second << ';';
        }
    }
    
    /** Helper function for reading conductivityMap from stream
     *
     * @param is Stream to read from
     * @param func Function for getting the memory id from the file id
     */
    void readConductivityMap(std::istream& is)
    {
        char separator;
        int tempId;
        double cond;
        for (auto n: conductivityMap) {
            is >> tempId;
            for (auto neighbor: node->getNeighborsMap()) {
                if (neighbor.second->getFileId() == tempId) {
                    is >> cond >> separator;
                    if (separator != ';') {
                        std::cout << "ERROR in CurrentWalk, ConductivityMap(): incorrect separator " << separator << ", should be (;)\n";
                    }
                    conductivityMap[neighbor.second->getId()] = cond;
                    break;
                }
            }
        }
    }
    
    void updateMeanFlow();
    void updateFlow(double dt);
    void updateConductivity(double dt);
    void updateCapacitance();
    virtual void updateNumberOfParticles();
    void (*updateFunction)();
    void updatePotential();
    std::shared_ptr<Node> node;
    ///Mean flow rate through the Node
    std::unordered_map<unsigned int,double> meanFlowMap;
    ///Conductivity of the Node
    std::unordered_map<unsigned int,double> conductivityMap;
    ///Capacitance of the Node
    double capacitance = 0;
    ///Random number generation state
    std::random_device rd;
    ///The element of the Algorithm
    std::shared_ptr<Element> element;
};

class CurrentWalkSource : public CurrentWalk {
public:
    void initialize(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
        CurrentWalk::initialize(n,element);
        if (auto a = dynamic_cast<PositionedSource<2>*>(&*n)) {
            productionRate = a->getProductionRate();
        }
    }
    
    void updateNumberOfParticles() {
        CurrentWalk::updateNumberOfParticles();
        node->setNumberOfParticles(productionRate + node->getNumberOfParticles());
    }
private:
    int productionRate = 0;
};

class CurrentWalkSink : public CurrentWalk {
public:
    void initialize(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
        CurrentWalk::initialize(n,element);
        if (auto a = dynamic_cast<PositionedSink<2>*>(&*n)) {
            removalRate = a->getRemovalRate();
        }
    }
    
    void updateNumberOfParticles() {
        CurrentWalk::updateNumberOfParticles();
        
        if (node->getNumberOfParticles() <= abs(removalRate)) {
            node->setNumberOfParticles(0);
        } else {
            node->setNumberOfParticles(removalRate + node->getNumberOfParticles());
        }
        
        
    }
private:
    int removalRate = 0;
};
