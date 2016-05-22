#pragma once

#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <utility>

class Router {
private:
	int beginCurX, beginCurY;
	Matrix tremauxRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	int countAdjacentPath(const Matrix& map, int x, int y);
	Matrix randomRouting(const Matrix& map, int curX, int curY);
public:
	Router() : beginCurX(0), beginCurY(0) {
		srand(time(NULL));
	};
	// return (x,y)
	std::pair<int, int> routing(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> simpleRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> howToGo(const Matrix& map, int curX, int curY, int x, int y); // (x, y)에 어떻게 가야하는지 dx, dy 반환
};