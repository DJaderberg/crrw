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
     */
    Node(std::unordered_map<unsigned long long,std::shared_ptr<Node>> n, std::unordered_map<unsigned long long,double> dist) {
        neighborsMap = n;
        lengthMap = dist;
    };
	/** Create a Node
	 */
    Node() : id(idCounter++) {
    };
    /**
     * Gets the neighbors
     *
     * @return A std::list of all neighbors to the Node.
     */
    virtual std::unordered_map<unsigned long long,std::shared_ptr<Node>> getNeighbors();
    /**
     * Add a new neighbor to the Node
     *
     * @param neighbor A Node that should be a neighbor to the current Node
     * @param distance The distance to the neighbor
     */
    virtual void insertNeighbor(std::shared_ptr<Node> neighbor, double distance);
	/**
	 * Create a new neighbor of the node if the node is not already connected 
	 * to the given neighbor.
	 *
     * @param neighbor A Node that should be a neighbor to the current Node
     * @param distance The distance to the neighbor
	 */
	virtual void insertNeighborUnique(std::shared_ptr<Node> neighbor, double distance);
    /**
     * Returns the id of the Node
     *
     * @return An unsigned long long of the nodes id.
     */
    unsigned long long getId();
    
    /**
     * Returns the fileId of the Node
     *
     * @return An long long of the nodes fileId.
     */
    long long getFileId();
    
    /**
     * Sets the fileId of the Node
     *
     * @param fileId An long long that will be set to the nodes fileId
     */
    void setFileId(long long fileId);
    
	/**
	 * Returns the number of particles in the Node
	 *
	 * @return The number of particles in the Node
	 */
	unsigned long long getNumberOfParticles();

	/**
	 * Sets the number of particles in the Node
	 *
	 * @param value The new value of the number of particles at the Node
	 */
	void setNumberOfParticles(unsigned long long value) {
		this->numberOfParticles = value;
	}
    
    ///Gets a map of the neigbors of the Node
    std::unordered_map<unsigned long long,std::shared_ptr<Node>> getNeighborsMap() {
        return neighborsMap;
    }

	///Gets a map of the distances to the neighbors of the Node
	std::unordered_map<unsigned long long, double> getDistanceMap() {
		return lengthMap;
	}

	///Gets the flow for id from the Node
	double getMeanFlow(unsigned long long id) {
		return meanFlowMap[id];
	}

	///Gets the potential, which is defined by the algorithm, of the Node
	double getPotential() {
		return potential;
	}
    
    ///Gets the conductivity for id from the Node
    double getConductivity(unsigned long long id) {
        return conductivityMap[id];
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
	std::unordered_map<unsigned long long, long long> flowMap;
    ///Mean flow rate through the Node
    std::unordered_map<unsigned long long,double> meanFlowMap;
    ///Cunductivity map
    std::unordered_map<unsigned long long,double> conductivityMap;
protected:
    ///Static ID counter
    static unsigned long long idCounter;
    ///Unique ID of the Node
    unsigned long long id;
    ///File id, initilized to -1 indicating that there is no corresponding file for this nod yet
    long long fileId = -1;
    
    /**
     * An unordered map containing all neighbors of the Node.
     */
    std::unordered_map<unsigned long long,std::shared_ptr<Node>> neighborsMap;
    ///The 'length in space' to all neighbors of the node
    std::unordered_map<unsigned long long,double> lengthMap;
    ///Number of elements at the node
    unsigned long long numberOfParticles = 0;
};



