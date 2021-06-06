#pragma once

#include <vector>
#include "Mower.h"
#include "lawn.h"

class MowingSimulation {
public:
	MowingSimulation(vector<Mower> m, Lawn l) : mowers(m), lawn(l) {};

	void start();

	void printPositions();

	vector<Mower> mowers;
	Lawn lawn;
private:
	bool isInsideGrid(Position p);
	bool isCollision(Position p);
	bool isMoveLegit(Position p);
	Position computeNextMove(Mower m);

	void mowParallel(const int startIdx, const int endIdx);
};

