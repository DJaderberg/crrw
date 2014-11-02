/** @file element.h
 * Contains declarations of Element
 */
#pragma once
#include <list>
#include <memory>
#include <array>

/**
 * An element that belongs to some node
 *
 * @author Kristoffer Jonsson, David Jäderberg
 */

class Element {
public:
    ///Reinforcement intensity
    const double q;
    ///Conductivity decrease rate
    const double lambda;
    ///Road maintenance cost factor
    const double mu;
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
     */
    Element(const double q, const double lambda, const double mu) : q(q), lambda(lambda), mu(mu) {};
};
