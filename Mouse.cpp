#include "Mouse.h"
#include <cstdio>


void Mouse::useTurn()
{
	std::pair<int, int> dst = router.routing(map, moveCount, curX, curY);
	//std::pair<int, int> d_dst = router.howToGo(map, curX, curY, dst.first, dst.second);
	//move(d_dst.first, d_dst.second);
	while(mana>=10){
		// ADD : check using MouseJR
		// ADD : control MouseJR and scan
	}
}

void Mouse::move(int dx, int dy)
{
	
	this->curX = this->curX + dx;
	this->curY = this->curY + dy;
	this->mana++;
	this->health--;
	
	if(isEscapeMaze()){
		// ADD : process when arrive the exit
	}
	else {
		// update map can see
		map.resize(curY+2, curX+2);
		for(int dy=-1; dy<=1; ++dy){
			for(int dx=-1; dx<=1; ++dx)
				map[curY+dy][curX+dx] = maze[curY+dy][curX+dx];
		}
		if(this->health <= 0)
		{	
			printf("We failed to find the exit...\n");
			exit(100);
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
	return curX==0 || (curY==0 && curX!=1) || curX==map.getCols()-1 || curY==map.getRows()-1;
}