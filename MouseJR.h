#pragma once

#include "Mouse.h"

class MouseJR {
	Matrix map;
	Matrix moveCount;
	Router router;
	int curX;
	int curY;
public:
	MouseJR() {}
	void init(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	void move(int dx, int dy);
	void updateMap3x3(const Matrix& map); // update this->map by map, at (curX, curY) center 3x3
	int getX();
	int getY();	
};