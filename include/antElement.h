/** @file antElement.h
 * Contains declarations of AntElement
 */
#pragma once
#include <list>
#include <memory>
#include <array>
#include "element.h"

/**
 * An AntElement that belongs to some node
 *
 * @author Kristoffer Jonsson
 */


class AntElement : public Element {
public:
    AntElement() : Element(0.0001, 0.001, 1.1, 1e-1, 10) {};
};
