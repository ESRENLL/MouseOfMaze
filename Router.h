#pragma once

#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <utility>

class Router {
private:
	Matrix randomRouting(const Matrix& map, int curX, int curY);
public:
	Router() { srand(time(NULL)); };
	// return (x,y)
	std::pair<int, int> routing(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> simpleRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> howToGo(const Matrix& map, int curX, int curY, int x, int y); // (x, y)에 어떻게 가야하는지 dx, dy 반환
};