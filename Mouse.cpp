#include "Mouse.h"
#include <cstdio>
#include <algorithm>
#include <iostream>


void Mouse::useTurn()
{
	std::pair<int, int> dst = router.routing(map, moveCount, curX, curY);
	std::pair<int, int> d_dst = router.howToGo(map, curX, curY, dst.first, dst.second);
	//printf("%d %d %d %d\n", dst.first, dst.second, d_dst.first, d_dst.second);
	move(d_dst.first, d_dst.second);
	//while(mana>=10){
	//	// ADD : check using MouseJR
	//	// ADD : control MouseJR and scan
	//}
}

void Mouse::move(int dx, int dy)
{
	this->curX = this->curX + dx;
	this->curY = this->curY + dy;
	this->mana++;
	this->health--;
	++moveCount[this->curY][this->curX];
	
	if(isEscapeMaze()){
		// ADD : process when arrive the exit
	}
	else {
		// update map can see
		int resizeRows = std::max(map.getRows(), curY+2);
		int resizeCols = std::max(map.getCols(), curX+2);
		map.resize(resizeRows, resizeCols);
		moveCount.resize(map.getRows(), map.getCols());
		for(int dy=-1; dy<=1; ++dy){
			for(int dx=-1; dx<=1; ++dx){
				if(curY+dy>=0)
					map[curY+dy][curX+dx] = maze[curY+dy][curX+dx];
			}
		}
		if(this->health <= 0)
		{	
			//printf("We failed to find the exit...\n");
			//exit(100);
		}
	}

}

void Mouse::scan(int x, int y)
{
	mana -= 10;

	// update map scanned
	for(int dy=-1; dy<=1; ++dy){
		for(int dx=-1; dx<=1; ++dx){
			if(maze.isIn(y+dy, x+dx))
				map[y+dy][x+dx] = maze[y+dy][x+dx];
			// 맵 범위를 벗어나면 맵 테두리를 알 수 있다.
			// 이를 통해 출구를 발견할 수 있는데, 이를 쥐는 현재 알 방법이 없다.
			// 방법??
		}
	}
}

int Mouse::getX()
{
	return this->curX;
}

int Mouse::getY()
{
	return this->curY;
}

bool Mouse::isEscapeMaze()
{
	return curX==0 || (curY==0 && curX!=1) || curX==maze.getCols()-1 || curY==maze.getRows()-1;
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
			if(row==curY && col==curX)
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