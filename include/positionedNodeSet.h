/** @file positionedNodeSet.h
 * Contains the declaration of PositionedNodeSet.
 */
#pragma once
#include "nodeSet.h"
#include "positionedNode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <omp.h>

const int NUM_RAND_DEVS = 1000;

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
        for (int i = 0; i < NUM_RAND_DEVS; ++i) {
            std::shared_ptr<std::random_device> rd(new std::random_device());
            randVect.push_back(rd);
        }
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
        for (int i = 0; i < NUM_RAND_DEVS; ++i) {
            std::shared_ptr<std::random_device> rd(new std::random_device());
            randVect.push_back(rd);
        }
        this->initializeAlgorithms(create, element);
        stream.close();
    };
	/**
	 * Create an empty and uninitalized PositionedNodeSet.
	 *
	 * For internal use only.
	 */
	PositionedNodeSet() {};
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
	/**
	 * Reinitialize the state of the algorithms, so that they may be drawn
	 *
	 * This only needs to be done after reading data from file.
	 */
	void reinitialize();
    ///Get positions
    std::unordered_map<unsigned int, std::array<double, 2>> getPositions();
    //Get PositionedNodes
    std::vector<std::shared_ptr<PositionedNode<2>>> getNodes();
    
    /** Write all data to stream
     *
     * @param os Stream to write to
     */
    void writeData(std::ostream& os) {
        for (auto a: algorithms) {
            a->writeData(os);
            os << '|';
        }
    }
    
    /** Write all data to stream
     *
     * @param os Stream to write to
     */
    void readData(std::istream& is) {
        char separator;
        for (auto a: algorithms) {
            a->readData(is);
            is >> separator;
            if (separator != '|') {
                std::cout << "ERROR in PositionedNodeSet, readData(): incorrect separator " << separator << ", should be (|)\n";
            }
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
	/**
	 * Find shortest path between two nodes
	 *
	 * This uses Dijkstra's algorithm
	 * @param source The source Node
	 * @return A map containing the shortest path from source to each node (in-memory node id is the key)
	 */
	std::pair<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, int>> shortestPath(unsigned int source);
	/**
	 * Write this set in METIS format.
	 *
	 * @param stream The output stream to write to
	 */
	void writeMETIS(std::ostream& stream);
	/**
	 * Write this set in METIS format.
	 *
	 * @param filename The file to write to
	 */
	void writeMETIS(const std::string& filename) {
        std::ofstream stream(filename);
        this->writeMETIS(stream);
        stream.close();
	}
	/**
	 * Reorder nodes and write to a file using a METIS partition.
	 *
	 * @param filename The file to write to
	 * @param numPart The number of partitions used by METIS
	 */
   void readMETIS(std::istream& input, std::ostream& output, unsigned int numPart);
	/**
	 * Reorder nodes and write to a file using a METIS partition.
	 *
	 * @param filename The file to write to
	 * @param numPart The number of partitions used by METIS
	 */
   void readMETIS(const std::string& input, const std::string& output, unsigned int numPart) {
        std::ifstream in(input);
        std::ofstream out(output);
        readMETIS(in, out, numPart);
        in.close();
        out.close();
   }   
   /**
	* Add a node to the set
	*
	* @param node The node to add to the set.
	*/
   void addNode(std::shared_ptr<PositionedNode<2>> node) {
	   positionedNodes.push_back(node);
   }
   void writeTGF(std::ostream& output);
   /**
	* Write this PositionedNodeSet to a TGF file
	* @param filename The file to write to
	*/
   void writeTGF(const std::string& filename) {
        std::ofstream out(filename);
		writeTGF(out);
        out.close();
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
    std::vector<std::shared_ptr<StorableAlgorithm>> algorithms;
    ///Map from the ids in the input stream to the actual ids of the Nodes
    std::unordered_map<int, unsigned int> idMap;
    ///Map from the actual ids of the Nodes to the ids in the input stream 
    std::unordered_map<unsigned int, int> inverseIdMap;
    ///Vector of random devices, one for each thread
    std::vector<std::shared_ptr<std::random_device>> randVect;
    ///Helper function to initialize algorithms
    ///@param create The function with which to create the Algorithm for each Node
    ///@param element The Element that the Algorithm should have
    void initializeAlgorithms(algorithmCreator create, std::shared_ptr<Element> element) {
        int i = 0;
        for (auto n : positionedNodes) {
            auto temp = std::dynamic_pointer_cast<StorableAlgorithm>(create(n, element));
            temp->setRd(randVect[i*omp_get_max_threads()/positionedNodes.size()]);
            algorithms.push_back(temp);
            ++i;
        }
    }
};

