#pragma once

#include "Matrix.h"
#include <string>
#include <iostream>

class MouseOfMazeSimulator {
private:
	Matrix maze;
public:
	bool readMap(std::string fileName);
	void simulate(bool simple=true, int observeInterval=300, std::ostream& out = std::cout);
	Matrix getMaze();
};