#include "Mouse.h"
#include <cstdio>
#include <algorithm>
#include <iostream>


void Mouse::useTurn()
{
	std::pair<int, int> ddst = router.tremauxRouting(map, moveCount, curRow, curCol);
	//printf("%d %d %d %d\n", dst.first, dst.second, d_dst.first, d_dst.second);
	move(ddst.first, ddst.second);
	//while(mana>=10){
	//	// ADD : check using MouseJR
	//	// ADD : control MouseJR and scan
	//}
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

	// update map scanned
	for(int drow=-1; drow<=1; ++drow){
		for(int dcol=-1; dcol<=1; ++dcol){
			if(maze.isIn(row+drow, col+dcol))
				map[row+drow][col+dcol] = maze[row+drow][col+dcol];
			// 맵 범위를 벗어나면 맵 테두리를 알 수 있다.
			// 이를 통해 출구를 발견할 수 있는데, 이를 쥐는 현재 알 방법이 없다.
			// 방법?? ==> row한계에 달하면 row한계를 담는 변수에 한계값 대입(초기값 -1로 미발견 구별)?
			//			col도 마찬가지.?
			//			출구를 발견하면 출구 변수에 값 대입.(초기값 -1로 미발견 구별?
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
	return curCol==0 || (curRow==0 && curRow!=1) || curCol==maze.getCols()-1 || curRow==maze.getRows()-1;
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