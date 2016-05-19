#pragma once

#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <utility>

class Router {
private:
public:
	Router() { srand(time(NULL)); };
	// return (x,y)
	std::pair<int, int> routing(const Matrix& map, const Matrix& moveCount, int curX, int curY) // LNK2019 ���忡�� �߻����� ��� ���Ͽ� �ڵ� ����
	{
		// ADD : Matrix predictedValue = predictAlgo1 * predictAlgo2 * predictAlgo3;
		Matrix predictedValue;
		std::pair<int, int> maxRowCol = predictedValue.getMaxRowCol();
		return std::make_pair(maxRowCol.second, maxRowCol.first);
	}
	std::pair<int, int> simpleRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY);
	std::pair<int, int> howToGo(const Matrix& map, int curX, int curY, int x, int y); // (x, y)�� ��� �����ϴ��� dx, dy ��ȯ
};