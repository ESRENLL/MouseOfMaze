#include "Mouse.h"
#include <cstdio>
#include <algorithm>
#include <iostream>


void Mouse::useTurn()
{
	std::pair<int, int> ddst;
	if(exitRow>=0) ddst = howToGo(exitRow, exitCol);
	if(ddst.first+ddst.second==0) ddst = tremauxRouting();
	move(ddst.first, ddst.second);	
	while(mana>=10){
		std::pair<int, int> scanPoint = searchScanPoint();
		scan(scanPoint.first, scanPoint.second);
	}
}

void Mouse::move(int drow, int dcol)
{
	this->curRow = this->curRow + drow;
	this->curCol = this->curCol + dcol;
	this->mana++;
	this->health--;
	++moveCount[this->curRow][this->curCol];
	
	if(isEscapeMaze()){
		// ADD : process when arrive the exit
	}
	else {
		// update map can see
		int resizeRows = std::max(map.getRows(), curRow+2);
		int resizeCols = std::max(map.getCols(), curCol+2);
		map.resize(resizeRows, resizeCols);
		moveCount.resize(map.getRows(), map.getCols());
		for(int drow=-1; drow<=1; ++drow){
			for(int dcol=-1; dcol<=1; ++dcol){
				if(curRow+drow>=0)
					map[curRow+drow][curCol+dcol] = maze[curRow+drow][curCol+dcol];
			}
		}
		if(this->health <= 0)
		{	
			//printf("We failed to find the exit...\n");
			//exit(100);
		}
	}

}

void Mouse::scan(int row, int col)
{
	mana -= 10;
	beginScanRow = row;
	beginScanCol = col;

	// update map scanned
	for(int drow=-1; drow<=1; ++drow){
		for(int dcol=-1; dcol<=1; ++dcol){
			int trow = row+drow;
			int tcol = col+dcol;
			if(maze.isIn(trow, tcol)){
				int resizeRows = std::max(map.getRows(), trow+1);
				int resizeCols = std::max(map.getCols(), tcol+1);
				map.resize(resizeRows, resizeCols);
				moveCount.resize(map.getRows(), map.getCols());
				map[trow][tcol] = maze[trow][tcol];
				if(isEndOfMaze(trow, tcol, mazeRows, mazeCols)){
					exitRow = trow;
					exitCol = tcol;
				}
			}
			else if(trow>=maze.getRows()) {
				// discover maze rows end
				mazeRows = maze.getRows();
				for(int col=0; col<3; ++col){
					if(isEndOfMaze(mazeRows-1, col, mazeRows, mazeCols)){
						exitRow = mazeRows-1;
						exitCol = col;
					}
				}
			}
			else if(tcol>=maze.getCols()) {
				// discover maze cols end
				mazeCols = maze.getCols();
				for(int row=mazeRows-3; row<mazeRows; ++row){
					if(isEndOfMaze(row, mazeCols-1, mazeRows, mazeCols)){
						exitRow = row;
						exitCol = mazeCols-1;
					}
				}
			}
		}
	}
}

int Mouse::getCurRow()
{
	return this->curRow;
}

int Mouse::getCurCol()
{
	return this->curCol;
}

bool Mouse::isEscapeMaze()
{
	return isEndOfMaze(curRow, curCol, maze.getRows(), maze.getCols());
}

bool Mouse::isEndOfMaze(int row, int col, int rows, int cols)
{
	return map.isIn(row,col) && map[row][col]==MAP_EMPTY && (col==0 || (row==0 && col!=1) || col==cols-1 || row==rows-1);
}

int Mouse::getHealth()
{
	return health;
}

void Mouse::printMap()
{
	const int rows = map.getRows();
	const int cols = map.getCols();
	for(int row=0; row<rows; ++row){
		for(int col=0; col<cols; ++col){
			char printChar;
			if(row==curRow && col==curCol)
				printChar = 'X';
			else {
				switch(map[row][col]){
				case MAP_EMPTY:	printChar=moveCount[row][col]%10+'0';  break;
				case MAP_WALL:	printChar='#'; break;
				default:		printChar=' '; break;
				}
			}
			std::cout << printChar << ' ';
		}
		std::cout << '\n';
	}
}

std::pair<int, int> Mouse::tremauxRouting()
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
	if(predictedValue[maxRowCol.first][maxRowCol.second]>0){
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
	}
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
	else
		beginRowColStk.push(maxRowCol);

	maxRowCol.first--;
	maxRowCol.second--;
	return maxRowCol;
}

std::pair<int, int> Mouse::howToGo(int dstRow, int dstCol)
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

std::pair<int, int> Mouse::searchScanPoint()
{
	// 1. search exit (left side -> bottom side -> right side -> top side)
	// 2. search way to current pos

	std::pair<int, int> ret(0,0); // (row, col)
	if(exitRow>=0) {
		// exit searched
		// use dfs, find empty adjacent fog 
		const int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // direction, (row,col)
		Matrix chkPushed = map;
		const int pushed = 10000;
		std::stack< std::pair<int,int> > dfs;
		chkPushed[exitRow][exitCol] = pushed;
		dfs.push(std::make_pair(exitRow, exitCol));
		while(!dfs.empty()){
			std::pair<int, int> top = dfs.top();
			dfs.pop();
			for(int d=0; d<4; ++d){
				int trow = top.first + dir[d][0];
				int tcol = top.second + dir[d][1];
				if(map.isIn(trow,tcol)){
					if(map[trow][tcol]==MAP_FOG){
						// scan point searched, return
						ret.first = trow + trow - top.first;
						ret.second = tcol + tcol - top.second;
						return ret;
					}
					else if(chkPushed[trow][tcol]!=pushed && map[trow][tcol]==MAP_EMPTY){
						chkPushed[trow][tcol] = pushed;
						dfs.push(std::make_pair(trow, tcol));
					}
				}
			}
		}
	}
	else if(mazeRows<0) {
		// search exit to left side(top->bottom)
		ret.first = beginScanRow;
		ret.second = 1;
		while(map.isIn(ret.first, 0) && map[ret.first][0]!=MAP_FOG){
			++ret.first;
		}
		++ret.first;
	}
	else if(mazeCols<0) {
		// search exit to down side(left->right)
		ret.first = mazeRows-2;
		ret.second = beginScanCol;
		while(map.isIn(mazeRows-1, ret.second) && map[mazeRows-1][ret.second]!=MAP_FOG){
			++ret.second;
		}
		++ret.second;
	}
	else if(beginScanRow>0) {
		// search exit to right side(bottom->top)
		ret.first = beginScanRow;
		ret.second = mazeCols-2;
		while(map.isIn(ret.first, mazeCols-1) && map[ret.first][mazeCols-1]!=MAP_FOG){
			--ret.first;
		}
		--ret.first;
		if(ret.first<0) ret.first = 0;
	}
	else {
		// search exit to top side(right->left)
		ret.first = 1;
		ret.second = beginScanCol;
		while(map.isIn(0, ret.second) && map[0][ret.second]!=MAP_FOG){
			--ret.second;
		}
		--ret.second;
		if(ret.second<0) ret.second = 0;
	}
	return ret;
}