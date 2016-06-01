#pragma once

#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <utility>
#include <stack>

class Router {
private:
	std::stack< std::pair<int, int> > beginRowColStk; // begin (row, col)
	int countAdjacentWall(const Matrix& map, int row, int col);
public:
	Router() {};
	std::pair<int, int> tremauxRouting(const Matrix& map, const Matrix& moveCount, int curRow, int curCol); // return (row,col)
	std::pair<int, int> howToGo(const Matrix& map, int curRow, int curCol, int row, int col); // (dstRow, dstCol)에 어떻게 가야하는지 drow, dcol 반환
};