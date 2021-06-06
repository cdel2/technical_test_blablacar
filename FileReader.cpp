#pragma once
#include "FileReader.h"
#include "Except.h"

static vector<string> parseLawn(string line) {
	istringstream record(line);
	string s;
	vector<string> tokens;

	int nbTokens = 0;
	while (record >> s) {
		tokens.push_back(s);
		++nbTokens;
	}

	if (nbTokens != 2)
		throw Except("Incorrect number of lawn values found");

	return tokens;
}

static vector<string> parseMower(string line, int lineNumber) {
	istringstream record(line);
	string s;
	vector<string> tokens;

	int nbTokens = 0;
	while (record >> s) {
		tokens.push_back(s);
		++nbTokens;
	}

	if (nbTokens != 3) {
		throw Except("Incorrect number of mower values found at line ", lineNumber);
	}

	return tokens;
}

Lawn FileReader::readLawn(string line) {
	vector<string> tokens = parseLawn(line);

	istringstream iss0(tokens[0]);
	istringstream iss1(tokens[1]);

	int xTopRight, yTopRight;
	iss0 >> xTopRight;
	iss1 >> yTopRight;

	if (iss0.fail() || iss1.fail() || xTopRight < 0 || yTopRight < 0)
		throw(Except("Incorrect lawn position found"));

	Lawn lawn;
	lawn.xTopRight = xTopRight;
	lawn.yTopRight = yTopRight;

	return lawn;
}

Mower FileReader::readMower(string line, unsigned int lineNumber, vector<Mower>& mowers) {
	vector<string> tokens = parseMower(line, lineNumber);

	Position p;
	Direction direction;

	istringstream iss0(tokens[0]);
	istringstream iss1(tokens[1]);

	int x, y;
	iss0 >> x;
	iss1 >> y;

	if (iss0.fail() || iss1.fail() || x < 0 || y < 0)
		throw(Except("Incorrect mower position found at line ", lineNumber));

	for (int i = 0; i < mowers.size(); i++) {
		if(mowers[i].pos.x == x && mowers[i].pos.y == y)
			throw(Except("Mower collision found at line ", lineNumber));

	}

	p.x = x;
	p.y = y;

	if(tokens[2].length() != 1)
		throw(Except("Incorrect mower direction found at line ", lineNumber));

	char dir = tokens[2][0];
	switch (dir) {
	case 'N':
		direction = Direction::N;
		break;
	case 'E':
		direction = Direction::E;
		break;
	case 'W':
		direction = Direction::W;
		break;
	case 'S':
		direction = Direction::S;
		break;
	default:
		throw(Except("Incorrect mower direction found at line ", lineNumber));
	}

	Mower m(p, direction);
	return m;
}

vector<Action> FileReader::readActions(string line, unsigned int lineNumber) {
	istringstream record(line);

	Action a;
	vector<Action> actions;
	for (int i = 0; i < line.length(); i++) {
		switch (line[i]) {
		case 'L':
			a = Action::L;
			break;
		case 'R':
			a = Action::R;
			break;
		case 'F':
			a = Action::F;
			break;
		default:
			throw(Except("Incorrect action found at line ", lineNumber));
		}
		actions.push_back(a);
	}

	return actions;
}

void FileReader::read(vector<Mower>& mowers, Lawn& lawn) {
	string line;
	ifstream input;

	int lineNumber = 0;

	input.open(fileName);
	if (!input.good()) {
		throw(Except("File not found"));
	}

	getline(input, line);
	lawn = readLawn(line);

	while (input.good()) {
		getline(input, line);
		Mower mower = readMower(line, ++lineNumber, mowers);

		getline(input, line);
		vector<Action> actions = readActions(line, ++lineNumber);

		mower.actions = actions;
		mowers.push_back(mower);
	}

	input.close();
}