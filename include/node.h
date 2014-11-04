/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <array>
#include <unordered_map>
#include "element.h"
#include <string>
#include <random>

/**
 * A node containing some number of elements
 *
 * @author David Jäderberg
 */
class Node {
public:
    /**
     * Create a new Node with neighbors n
     *
     * @param n Neighbors of the new Node
     * @param dist Distance to each neighbor, in same order as n
	 * @param e The Element of the Node
     */
    Node(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist, std::shared_ptr<Element> e) : Node(e) {
        neighborsMap = n;
        lengthMap = dist;
    };
	/** Create a Node with only an element
	 *
	 * @param e The Element of the Node
	 */
    Node(std::shared_ptr<Element> e) : id(idCounter++), element(e) {
    };
    /**
     * Gets the neighbors
     *
     * @return A std::list of all neighbors to the Node.
     */
    virtual std::unordered_map<unsigned int,std::shared_ptr<Node>> getNeighbors();
    /**
     * Add a new neighbor to the Node
     *
     * @param neighbor A Node that should be a neighbor to the current Node
     * @param distance The distance to the neighbor
     */
    virtual void insertNeighbor(std::shared_ptr<Node> neighbor, double distance);
    
    /**
     * Returns the id of the Node
     *
     * @return An unsigned int of the nodes id.
     */
    unsigned int getId();
    
	/**
	 * Returns the number of particles in the Node
	 *
	 * @return The number of particles in the Node
	 */
	unsigned int getNumberOfParticles();

	/**
	 * Prepare a step by filling the changeMap
	 */
	virtual void prepareStep(double dt);
    /**
     * Allow elements at node to move, if needed
     */
    virtual void takeStep(double dt);
    
    /**
     * Standard toString method
     */
    virtual std::string toString();
    
    virtual ~Node() {
    }
protected:
    ///Static ID counter
    static unsigned int idCounter;
    ///Unique ID of the Node
    unsigned int id;
    ///Helper function to update number of particles
    void updateNumberOfParticles();
    ///Helper function to update conductivity
    void updateConductivity();
    ///Helper function to update capacitance
    void updateCapacitance();
    ///Helper function to calculate potential
    double calculatePotential();
    
    /**
     * An unordered map containing all neighbors of the Node.
     */
    std::unordered_map<unsigned int,std::shared_ptr<Node>> neighborsMap;
    ///The 'length in space' to all neighbors of the node
    std::unordered_map<unsigned int,double> lengthMap;
    ///The element of the Node
    std::shared_ptr<Element> element;
    ///Number of elements at the node
    unsigned int numberOfParticles = 0;
    ///Mean flow rate through the node
    std::unordered_map<unsigned int,double> meanFlowMap;
    ///Conductivity of the node
    std::unordered_map<unsigned int,double> conductivityMap;
    ///Capacitance of the node
    double capacitance = 0;
	///How many elements will move from this Node to each neighbor in the next time step
	std::unordered_map<unsigned int, unsigned int> changeMap;
	//Seed for RNG
	std::random_device rd;
};



