#pragma once

#include "Matrix.h"
#include <string>

class MouseOfMazeSimulator {
private:
	Matrix maze;
public:
	bool readMap(std::string fileName);
	void simulate(bool simple=true, bool observe=false, int observeInterval=300);
	Matrix getMaze();
};