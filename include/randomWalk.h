/** @file randomWalk.h
 * Contains declarations of RandomWalk
 */
#pragma once
#include <memory>
#include "algorithm.h"

class RandomWalk : public Algorithm {
public:
	void prepareStep(double dt);
	void takeStep(double dt);
private:
};
