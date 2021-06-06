#pragma once

#include <vector>
#include "direction.h"
#include "action.h"
#include "position.h"

using namespace std;

class Mower {
public:
	Mower() {};

	Mower(Position p, Direction d) : pos(p), dir(d) {};

	Mower(Position p, Direction d, vector<Action> a) : actions(a), pos(p), dir(d) {};

	void turnLeft();

	void turnRight();

	void moveForward();

	Position pos;
	Direction dir;
	vector<Action> actions;
};