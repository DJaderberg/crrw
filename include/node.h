/** @file node.h
 * Contains declarations of Node and its subclass Source
 */
#pragma once
#include <list>
#include <memory>
#include <array>
#include "element.h"

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
		Node(std::list<std::shared_ptr<Node>> n, std::list<double> dist, std::shared_ptr<Element> e) : neighbors(n), length(dist), element(e) {};
		Node(std::shared_ptr<Element> e) : element(e) {};
		/**
		 * Gets the neighbors
		 *
		 * @return A std::list of all neighbors to the Node.
		 */
		virtual std::list<std::shared_ptr<Node>> getNeighbors();
		/**
		 * Add a new neighbor to the Node
		 *
		 * @param neighbor A Node that should be a neighbor to the current Node
		 * @param distance The distance to the neighbor
		 */
		virtual void insertNeighbor(std::shared_ptr<Node> neighbor, double distance);
		/**
		 * Allow elements at node to move, if needed
		 */
		void takeStep();
		virtual ~Node() {
		}
	private:
		/**
		 * A list containing all neighbors of the Node.
		 */
		std::list<std::shared_ptr<Node>> neighbors;
		///The 'length in space' to all neighbors of the node
		std::list<double> length;
		///The element of the Node
		std::shared_ptr<Element> element;
		///Number of elements at the node
		double potential = 0; //TODO: Should this be unsigned int?
		///Flow rate through the node
		std::list<double> current;
		///Conductivity of the node
		std::list<double> conductivity;
		///Capacitance of the node
		double capacitance = 0;
};



