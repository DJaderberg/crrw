/** @file linearAntElement.h
 * Contains declarations of LinearAntElement
 */
#pragma once
#include <list>
#include <memory>
#include <array>
#include "element.h"

/**
 * An LinearAntElement that belongs to some node
 *
 * @author Kristoffer Jonsson
 */


class LinearAntElement : public Element {
public:
    LinearAntElement() : Element(0.0001, 0.001, 1, 5e-2, 10) {};
};

