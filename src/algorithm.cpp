/** @file algorithm.cpp
 * Contains definitions of functions in the class Algorithm
 */
#include "algorithm.h"

void Algorithm::setRd(std::shared_ptr<std::random_device> rd) {
    this->rd = rd;
}