/** @file nodeSet.h
 * Contains the declaration of NodeSet.
 */
//
//  Created by Kristoffer Jonsson on 03/11/14.
//
#pragma once
#include "node.h"
#include "storableAlgorithm.h"
#include <istream>
#include <fstream>
#include <vector>

/**
 * A class that holds and manipulates a set of Nodes
 */
class NodeSet {
public:
	/**
	 * Create a NodeSet from a stream
	 *
	 * @param input A stream with containing a set fo Nodes specified by TGF.
	 * @param create The function with which to create the Algorithm for each Node
	 * @param element The element to use when calling the function create
	 */
    NodeSet(std::istream input, algorithmCreator create, std::shared_ptr<Element> element) {
		this->parseTGF(input);
		this->initializeAlgorithms(create, element);
	}
	/** Create a NodeSet from a filename
	 *
	 * The file is opened as a stream and the NodeSet is constructed as if that 
	 * stream had been supplied
	 *
	 * @param filename The name of the file to use as input
	 * @param create The function with which to create the Algorithm for each Node
	 * @param element The element to use when calling the function create
	 */
    NodeSet(const std::string& filename, algorithmCreator create, std::shared_ptr<Element> element) {
		std::ifstream stream(filename);
		this->parseTGF(stream);
		this->initializeAlgorithms(create, element);
	};

	/**
	 * Create an Algorithm for each Node currently in the set
	 *
	 * @param create A function which returns a shared_ptr to an instance of some subclass of Algorithm when called with parameters with types (Node,Element). See also the typedef of algorithmCreator
	 * @param element The element to use when calling the function create
	 */
	void initializeAlgorithms(algorithmCreator create, std::shared_ptr<Element> element) {
		for (auto n : nodes) {
			auto temp = create(n, element);
			algorithms.push_back(temp);
		}
	}
	/// Return a string representation of the NodeSet
	virtual std::string toString();
	/// Return the number of particles at each Node in the NodeSet
	virtual std::vector<unsigned long long> numberOfParticles();
	/**
	 * Make one time step
	 *
	 * @param dt Length of the time step
	 */
	void takeStep(double dt);
protected:
	/** Create a dummy NodeSet, which shouldn't be used
	 */
	NodeSet() {};

	/**
	 * Read a stream containing a TGF NodeSet and store it in the member nodes.
	 *
	 * The formatting of the stream is assumed to be a kind of trivial graph 
	 * format (TGF) where the stream begins with a list of integers, each one 
	 * optionally followed by a production rate (positive for sinks, negative for 
	 * drains), separated by a new-line character ("\n"). This is followed by a line
	 * consisting of a hash ("#") followed by a new-line. Each remaining line 
	 * in the stream then consists of two integers followed by a floating point 
	 * number and a new-line. This specifies a connection from the first Node to 
	 * the second Node with the distance given by the floating point number.
	 *
	 * @param input A stream with containing a set fo Nodes specified by TGF.
	 *
	 * @author David Jäderberg
	 */
    void parseTGF(std::istream& input);
	///A vector containing all Nodes in the set
	std::vector<std::shared_ptr<Node>> nodes;
	///A vector containing all Algorithms in the set
	std::vector<std::shared_ptr<Algorithm>> algorithms;
	///Map from the ids in the input stream to the actual ids of the Nodes
	std::unordered_map<long long, unsigned long long> idMap;
};

