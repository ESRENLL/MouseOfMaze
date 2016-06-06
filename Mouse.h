#pragma once

#include "Matrix.h"
#include <utility>
#include <stack>
#include <iostream>

class Mouse {
private:
	const Matrix maze;
	Matrix map; // enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };
	Matrix moveCount; // 이동한 횟수(default 0)
	int curRow;
	int curCol;
	int health;
	int mana;

	// moues's view point
	int exitRow; // default = -1 (undiscovered)
	int exitCol; // default = -1 (undiscovered)
	int mazeRows; // default = -1 (undiscovered)
	int mazeCols; // default = -1 (undiscovered)

private:
	bool isEndOfMaze(int row, int col, int rows	, int cols); // by mouse
	void move(int drow, int dcol); // 이동 후 맵(+moveCount, health, mana, x, y) 갱신
	void scan(int row, int col); // 스캔 후 맵 및 마나 갱신
	std::stack< std::pair<int, int> > beginRowColStk; // begin (row, col)
	std::pair<int, int> tremauxRouting(); // return (row,col)
	int beginScanRow, beginScanCol;
	std::pair<int, int> searchScanPoint();
	std::pair<int, int> howToGo(int dstRow, int dstCol); // (dstRow, dstCol)에 어떻게 가야하는지 drow, dcol 반환

public:
	Mouse(const Matrix& maze)
	: maze(maze), map(), curRow(0), curCol(1), health(2*maze.getRows()*maze.getCols()), mana(0)
	, exitRow(-1), exitCol(-1), mazeRows(-1), mazeCols(-1), beginScanRow(0), beginScanCol(0)
	{
		map.setInitValue(MAP_FOG);
		map.resize(2, 3);
		moveCount.setInitValue(0);
		moveCount.resize(2, 3);
		++moveCount[0][1];
		for(int row=0; row<2; ++row){
			for(int col=0; col<3; ++col)
				map[row][col] = maze[row][col];
		}
	}
	~Mouse() {}
	void useTurn();
	int getCurRow(); // 자신의 현재위치 x를 반환
	int getCurCol(); // 자신의 현재위치 y를 반환
	bool isEscapeMaze(); // 미로 탈출 여부 반환
	int getHealth();
	void printMap(std::ostream& out = std::cout);
};
