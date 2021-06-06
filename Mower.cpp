#pragma once
#include "Mower.h"

#include <iostream>
using namespace std;

void Mower::turnRight() {
	int i = dir + 1;
	dir = (Direction)(i > 3 ? 0 : i);
	cout << "direction : " << dir << endl;
}


void Mower::turnLeft() {
	int i = dir - 1;
	dir = (Direction)(i < 0 ? 3 : i);
	cout << "direction : " << dir << endl;
}

void Mower::moveForward() {
	switch (dir) {
		case Direction::N:
			++pos.y;
			break;
		case Direction::E:
			++pos.x;
			break;
		case Direction::W:
			--pos.x;
			break;
		case Direction::S:
			--pos.y;
			break;
	}
	cout << "position : " << pos.x << " " << pos.y << endl;

}