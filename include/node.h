/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <array>
#include <unordered_map>
#include <random>
#include "element.h"
#include <string>

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
    Node(std::unordered_map<unsigned int,std::shared_ptr<Node>> n, std::unordered_map<unsigned int,double> dist) {
        neighborsMap = n;
        lengthMap = dist;
    };
	/** Create a Node with only an element
	 *
	 * @param e The Element of the Node
	 */
    Node() : id(idCounter++) {
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
	 * Sets the number of particles in the Node
	 *
	 * @param value The new value of the number of particles at the Node
	 */
	void setNumberOfParticles(unsigned int value) {
		this->numberOfParticles = value;
	}

	///Gets a map of the distances to the neighbors of the Node
	std::unordered_map<unsigned int, double> getDistanceMap() {
		return lengthMap;
	}

	///Gets the flow map from the Node
	double getMeanFlow(unsigned int id) {
		return meanFlowMap[id];
	}

	///Gets the potential, which is defined by the algorithm, of the Node
	double getPotential() {
		return potential;
	}

    /**
     * Standard toString method
     */
    virtual std::string toString();
    
    virtual ~Node() {
    }
	///The potential at the node
	double potential = 0;
	//Actual flow rate (probabilistic) through the node
	std::unordered_map<unsigned int, double> flowMap;
    ///Mean flow rate through the Node
    std::unordered_map<unsigned int,double> meanFlowMap;
protected:
    ///Static ID counter
    static unsigned int idCounter;
    ///Unique ID of the Node
    unsigned int id;
    
    /**
     * An unordered map containing all neighbors of the Node.
     */
    std::unordered_map<unsigned int,std::shared_ptr<Node>> neighborsMap;
    ///The 'length in space' to all neighbors of the node
    std::unordered_map<unsigned int,double> lengthMap;
    ///Number of elements at the node
    unsigned int numberOfParticles = 0;
};



