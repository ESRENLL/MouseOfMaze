#pragma once

#include "Mouse.h"

class MouseJR : Mouse {
public:
	MouseJR() : Mouse(987654321) {}
	void init(const Matrix& map, int curX, int curY);
	void move(int dx, int dy);
	int getX();
	int getY();
};