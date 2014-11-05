/** @file positionedNodeSet.h
 * Contains the declaration of PositionedNodeSet.
 */
#pragma once
#include "nodeSet.h"
#include "positionedNode.h"

class PositionedNodeSet : public NodeSet {
public:
	/**
	 * Create a NodeSet from a stream
	 *
	 * @param input A stream with containing a set fo Nodes specified by TGF.
	 * @param element The Element to assign to all created Nodes
	 */
	PositionedNodeSet(std::istream input, std::shared_ptr<Element> e) {
		this->parseTGF(input, e);
	}
	/** Create a NodeSet from a filename
	 *
	 * The file is opened as a stream and the NodeSet is constructed as if that 
	 * stream had been supplied
	 *
	 * @param filename The name of the file to use as input
	 * @param element The Element to assign to all created Nodes
	 */
	PositionedNodeSet(const std::string& filename, std::shared_ptr<Element> e) {
		std::ifstream stream(filename);
		this->parseTGF(stream, e);
	};
	/// Return a string representation of the NodeSet
	std::string toString();
	/// Return the number of particles at each Node in the NodeSet
	std::vector<unsigned int> numberOfParticles();
	/**
	 * Make one time step
	 *
	 * @param dt Length of the time step
	 */
	void takeStep(double dt);
	///Get positions
	std::unordered_map<unsigned int, std::array<double, 2>> getPositions();
	//Get PositionedNodes
	std::vector<std::shared_ptr<PositionedNode<2>>> getNodes();
private:
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
	 * @param e The Element to assign to all created Nodes
	 *
	 * @author David Jäderberg
	 */
    void parseTGF(std::istream& input, std::shared_ptr<Element> e);
	///A vector containing all nodes in the set
	std::vector<std::shared_ptr<PositionedNode<2>>> positionedNodes;
	///Map from the ids in the input stream to the actual ids of the Nodes
	std::unordered_map<int, unsigned int> idMap;
};

