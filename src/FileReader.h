#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Mower.h"
#include "action.h"
#include "lawn.h"
#include "position.h"
#include "direction.h"

using namespace std;

class FileReader
{
public:
	FileReader(string f) : fileName(f) {};

	void read(vector<Mower>& mowers, Lawn& lawn);

private:
	Lawn readLawn(string line);
	Mower readMower(string line, unsigned int lineNumber, vector<Mower>& mowers);
	vector<Action> readActions(string line, unsigned int lineNumber);

	string fileName;
};

