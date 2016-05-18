#pragma once

#include <cstdlib>
#include <ctime>
#include <utility>
#include "Matrix.h"

class Router {
private:
public:
	Router() { srand(time(NULL)); };
	// return (x,y)
	std::pair<int, int> routing(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> simpleRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> howToGo(const Matrix& map, int curX, int curY, int x, int y); // (x, y)�� ��� �����ϴ��� dx, dy ��ȯ
};