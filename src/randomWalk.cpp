/** @file randomWalk.cpp
 * Contains definitions of functions in the class RandomWalk
 */
#include "randomWalk.h"

void RandomWalk::prepareStep(double dt) {
}

void RandomWalk::takeStep(double dt) {
}

std::shared_ptr<Algorithm> RandomWalk::create(std::shared_ptr<Node> n, std::shared_ptr<Element> element) {
	std::shared_ptr<RandomWalk> a;
	if (dynamic_cast<PositionedSource<2>*>(&*n)) {
		a.reset(new RandomWalkSource());
	} else if (dynamic_cast<PositionedSink<2>*>(&*n)) {
		a.reset(new RandomWalkSink());
	} else {
		a.reset(new RandomWalk());
	}
	a->initialize(n, element);
	return a;
}
