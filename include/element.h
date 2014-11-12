/** @file element.h
 * Contains declarations of Element
 */
#pragma once
#include <list>
#include <memory>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * An element that belongs to some node
 *
 * @author Kristoffer Jonsson, David Jäderberg
 */

class Element {
public:
    ///Reinforcement intensity
    double q;
    ///Conductivity decrease rate
    double lambda;
    ///Road maintenance cost factor
    double mu;
	///Minimal conductivity
	double Dmin;
	///Production rate of each Source
	unsigned int productionRate;
    /**
     * Construct an element with certain parameters
     *
     * Each Element with the same parameters is exactly the same as any other
     * element with the same parameters and can be used interchangably. This
     * means that only one Element with the same parameters ever needs to be
     * constructed.
     *
     * @param q Reinforcement intensity
     * @param lambda Conductivity decrease rate
     * @param mu Road maintenance cost factor
	 * @param Dmin Minimum possible conductivity on an edge
	 * @param productionRate Production rate of each Source
     */
    Element(const double q, const double lambda, const double mu, const double Dmin, unsigned int productionRate) : q(q), lambda(lambda), mu(mu), Dmin(Dmin), productionRate(productionRate) {};
	/**
	 * Write the contents of an Element to a file
	 *
	 * @param filename A string of the filename of the file to write to
	 */
	void writeData(const std::string& filename) {
        std::ofstream stream(filename);
		writeData(stream);
		stream.close();
	}
	/**
	 * Write the contents of an Element to a stream
	 *
	 * @param output The stream to write to
	 */
	void writeData(std::ostream& output) {
		writeData(output, ';');
	}
	/**
	 * Write the contents of an Element to a stream
	 *
	 * @param output The stream to write to
	 * @param separator The character to separate each value with
	 */
	void writeData(std::ostream& output, char separator) {
		output << q << separator;
		output << lambda << separator;
		output << mu << separator;
		output << Dmin << separator;
		output << productionRate << separator;
	}

	/**
	 * Read parameters of an element from a file and overwrite the contents
	 * of this Element with those parameters.
	 *
	 * @param filename Filename of the file to read from
	 */
	void readData(std::string line) {
		char temp;
		std::istringstream iss(line);
		iss >> q >> temp >> lambda >> temp >> mu >> temp >> Dmin >> temp >> productionRate >> temp;
	}
};
