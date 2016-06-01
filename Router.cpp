#include "Router.h"

#include <stack>
#include <vector>

#define MAX_COUNT 9999

std::pair<int, int> Router::tremauxRouting(const Matrix& map, const Matrix& moveCount, int curRow, int curCol)
{
	// return (drow,dcol)

	Matrix predictedValue; // 3x3, [1][1] = current pos.
	predictedValue.setInitValue(0);
	predictedValue.resize(3,3);

	// if adjacent moveCount==0 then go
	// else pop stack and return
	const int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	for(int d=0; d<4; ++d){
		int trow = curRow + dir[d][0];
		int tcol = curCol + dir[d][1];
		if(map.isIn(trow, tcol) && map[trow][tcol]==MAP_EMPTY && moveCount[trow][tcol]==0)
			predictedValue[dir[d][0]+1][dir[d][1]+1] = 1;
	}
	std::pair<int, int> maxRowCol = predictedValue.getMaxRowCol();
	if(predictedValue[maxRowCol.first][maxRowCol.second]==0){
		// adjacent moveCount==0 is not exist
		// just back to stk
		if(beginRowColStk.empty()) // no exit
			return std::make_pair(-1, -1);
		maxRowCol = beginRowColStk.top();
		beginRowColStk.pop();
		maxRowCol.first = abs(maxRowCol.first-2);
		maxRowCol.second = abs(maxRowCol.second-2);
	}
	else {
		// adjacent moveCount==0 is exist
		// apply other algo, select

		// prevent move to inner space
		for(int d=0; d<4; ++d){
			if(predictedValue[dir[d][0]+1][dir[d][1]+1]>0){
				int temp = 0;
				std::swap(temp, predictedValue[dir[d][0]+1][dir[d][1]+1]);
				for(int row=-1; row<=1; ++row){
					for(int col=-1; col<=1; ++col){
						int trow = curRow + dir[d][0] + row;
						int tcol = curCol + dir[d][1] + col;
						if(map.isIn(trow,tcol) && map[trow][tcol]==MAP_WALL){
							predictedValue[dir[d][0]+1][dir[d][1]+1] = temp;
							break;
						}
					}
				}
			}
		}
		maxRowCol = predictedValue.getMaxRowCol();
		beginRowColStk.push(maxRowCol);
	}
	maxRowCol.first--;
	maxRowCol.second--;
	return maxRowCol;
}

std::pair<int, int> Router::howToGo(const Matrix& map, int curRow, int curCol, int dstRow, int dstCol)
{
	// return drow, dcol

	if(curRow==dstRow && curCol==dstCol) return std::make_pair(0,0);

	const int beginCount = 10000;
	const int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // direction, (row,col)
	std::stack< std::pair<int, int> > before, next; // next (row,col)
	Matrix mapClone = map;

	// find (x,y)
	before.push(std::make_pair(curRow, curCol));
	mapClone[curRow][curCol] = beginCount;
	while(true){
		if(before.empty()) return std::make_pair(0, 0); // cannot
		
		while(!before.empty()) {
			std::pair<int, int> top = before.top();
			if(top.first==dstRow && top.second==dstCol) break;
			before.pop();
			for(int d=0; d<4; ++d) {
				int trow = top.first+dir[d][0];
				int tcol = top.second+dir[d][1];
				if(mapClone.isIn(trow,tcol) && mapClone[trow][tcol]==MAP_EMPTY) {
					next.push(std::make_pair(trow,tcol));
					mapClone[trow][tcol] = mapClone[top.first][top.second]+1;
				}
			}
		}
		if(!before.empty()) break;
		if(next.empty()) return std::make_pair(0,0);
		before.swap(next);
	}
	
	// back from (x,y)
	int backRow = dstRow;
	int backCol = dstCol;
	while(abs(backRow-curRow)+abs(backCol-curCol)!=1) {
		for(int d=0; d<4; ++d) {
			int trow = backRow+dir[d][0];
			int tcol = backCol+dir[d][1];
			if(mapClone.isIn(trow,tcol) && mapClone[trow][tcol]==mapClone[backRow][backCol]-1) {
				backRow = trow;
				backCol = tcol;
				break;
			}
		}
	}
	return std::make_pair(backRow-curRow, backCol-curCol);
}