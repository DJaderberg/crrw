/** @file positionedNodeSet.h
 * Contains the declaration of PositionedNodeSet.
 */
#pragma once
#include "nodeSet.h"
#include "positionedNode.h"
#include <fstream>
#include <iostream>
#include <sstream>

class PositionedNodeSet : public NodeSet {
public:
    /**
     * Create a NodeSet from a stream
     *
     * @param input A stream with containing a set fo Nodes specified by TGF.
     * @param create The function with which to create the Algorithm for each Node
     */
    PositionedNodeSet(std::istream input, algorithmCreator create, std::shared_ptr<Element> element) {
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
     */
    PositionedNodeSet(const std::string& filename, algorithmCreator create, std::shared_ptr<Element> element) {
        std::ifstream stream(filename);
        this->parseTGF(stream);
        this->initializeAlgorithms(create, element);
        stream.close();
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
    
    /** Write number of particles to stream
     *
     * @param stream to write to
     */
    void writeNumPartToStream(std::ostream& os)
    {
        // write out individual members of s with an end of line between each one
        for (auto n: positionedNodes) {
            os << n->getNumberOfParticles() << " ";
        }
        os << "\n";
    }

    
    /** Read number of particles to stream
     *
     * @param stream to read from
     */
    void readNumPartFromStream(std::istream& is, int lineNumber)
    {
        // read in individual members of s
        std::string line;
        
        for ( int i = lineNumber; i > 0; --i ) {
            is.ignore( INT_MAX, '\n' );
        }
        std::getline( is, line );
        std::istringstream iss(line);
        int N, i = 0;
        
        //If we can extract an Int
        while (iss >> N) {
            positionedNodes[i]->setNumberOfParticles(N);
            i++;
        }
    }
	/**
	 * Get the file id of a Node
	 *
	 * @param id The in-memory id of the Node
	 * @return The file id of the Node
	 */
	int getFileId(unsigned int id) {
		return inverseIdMap[id];
	}
	/**
	 * Get the in-memory id of a Node
	 *
	 * @param id The file id of the Node
	 * @return The in-memory id of the Node
	 */
	unsigned int getMemoryId(int id) {
		return idMap[id];
	}
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
     * @param input A stream with containing a set of Nodes specified by TGF.
     * @param e The Element to assign to all created Nodes
     *
     * @author David Jäderberg
     */
    void parseTGF(std::istream& input);
    ///A vector containing all Nodes in the set
    std::vector<std::shared_ptr<PositionedNode<2>>> positionedNodes;
    ///A vector containing all Algorithms in the set
    std::vector<std::shared_ptr<Algorithm>> algorithms;
    ///Map from the ids in the input stream to the actual ids of the Nodes
    std::unordered_map<int, unsigned int> idMap;
    ///Map from the actual ids of the Nodes to the ids in the input stream 
    std::unordered_map<unsigned int, int> inverseIdMap;
    ///Helper function to initialize algorithms
    ///@param create The function with which to create the Algorithm for each Node
    ///@param element The Element that the Algorithm should have
    void initializeAlgorithms(algorithmCreator create, std::shared_ptr<Element> element) {
        for (auto n : positionedNodes) {
            auto temp = create(n, element);
            algorithms.push_back(temp);
        }
    }
};

