#pragma once

#include "MowingSimulation.h"
#include "threading.h"
#include <future>

#include <iostream>

using namespace std;

bool MowingSimulation::isInsideGrid(Position p) {
	return (p.x >= lawn.xBottomLeft && p.y >= lawn.yBottomLeft && p.x <= lawn.xTopRight && p.y <= lawn.yTopRight);
}

bool MowingSimulation::isCollision(Position p) {
	for (int i = 0; i < mowers.size(); i++) {
		if (mowers[i].pos.x == p.x && mowers[i].pos.y == p.y)
			return 1;
	}

	return 0;
}

bool MowingSimulation::isMoveLegit(Position p) {
	return (isInsideGrid(p) && !isCollision(p));
}

Position MowingSimulation::computeNextMove(Mower m) {
	Position p;
	p.x = m.pos.x;
	p.y = m.pos.y;

	switch (m.dir) {
		case Direction::N:
			++p.y;
			break;
		case Direction::E:
			++p.x;
			break;
		case Direction::W:
			--p.x;
			break;
		case Direction::S:
			--p.y;
			break;
	}

	return p;
}

void  MowingSimulation::mowParallel(int startIdx, int endIdx) {
	for (int i = startIdx; i < endIdx; i++) {
		for (int j = 0; j < mowers[i].actions.size(); j++) {
			switch (mowers[i].actions[j]) {
			case Action::L:
				mowers[i].turnLeft();
				break;
			case Action::R:
				mowers[i].turnRight();
				break;
			case Action::F:
				Position p = computeNextMove(mowers[i]);
				if (isMoveLegit(p)) {
					mowers[i].moveForward();
				}
			}
		}
	}
}

void MowingSimulation::start() {
	const auto threads = getHardwareThreadCount();
	const auto iters = getIterationIndices(mowers.size());

	auto validThreads{ threads };

	if (iters.size() - 1 < threads) {
		validThreads = iters.size() - 1;
	}

	vector<future<void>> futures(validThreads);

	for (unsigned i = 0; i < validThreads; i++) {
		futures[i] = async(launch::async, &MowingSimulation::mowParallel, this, iters[i], iters[i+1]);

	}

	for (auto& future : futures) {
		future.get();
	}
}

void MowingSimulation::printPositions() {
	for (int i = 0; i < mowers.size(); i++) {
		cout << mowers[i].pos.x << " " << mowers[i].pos.y << endl;
	}
}