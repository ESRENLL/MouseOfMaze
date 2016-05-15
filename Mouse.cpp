#include "Mouse.h"
#include "Matrix.h"
#include <ctime>
#include <cstdlib>
#include <stdio.h>

#define MAX_COUNT 9999
enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };

//문제 1: this->map.getValue(curX, curY + 1) << 함수 쓰는법
//문제 2: 현재위치에서 사방의 타일의 값을 읽어야하는데, 전체 맵을 저장한 배열을 어떻게 불러와야...
//문제 3: exit을 구분하는 방법

void Mouse::routing()
{
	typedef struct possiblePath
	{
		int x;
		int y;
		int value;
	}path;
	int i;
	int num = 0;
	path min;
	min.value = MAX_COUNT;

	for(i = -1; i <= 1; i++)
	{
		for(j = -1; j <= 1; j++)
		{
			if( i + j == 1 || i + j == -1)
			{
				if( ( this->maze[curX + i][curY + j] == MAP_WALL))//벽일 때
					map[curX + i][curY + j] = MAP_WALL;//access error일어나지 않을까...?
				else//벽이 아닐떄
					map[curX + i][curY + j] = maze[curX + i][curY + j];//input maze data to map array
				if(min.value > moveCount[curX + i][curY + j])//decide which block has minimum value
				{
					min.value = moveCount[curX + i][curY + j];
					min.x = curX + i;
					min.y = curY + j;
				}
				else if(min.value == map[curX + i][curY + j])//if there is 2 minimum value in the 4 block
				{
					srand(time(NULL));
					if(rand() % 2 == 1)//make 0 or 1 to decide randomly blocks which have same value 
					{
						min.value = moveCount[curX + i][curY + j];
						min.x = curX + i;
						min.y = curY + j;
					}
					else
						min = min;
				}
			}
			else//if i + j != 1 or -1
				continue;
		}
	}


	this->moveCount.setInitValue((this->moveCount.getValue(curX, curY))++);
	this->moveCount.resize(curX, curY);
	move(min.x, min.y);
}

void Mouse::move(int dx, int dy)
{
	
	this->curX = this->curX + dx;
	this->curY = this->curY + dy;
	this->mana++;
	this->health--;
	
	if(curX==0 || (curY==0 && curX!=1) || curX==map.getCols()-1 || curY==map.getRows()-1){
		// process when arrive the exit
	}
	else if(this->health <= 0)
	{	
		printf("We failed to find the exit...\n");
		exit(100);
	}
}

void Mouse::scan(int x, int y)
{

}

void Mouse::consumeMana()
{

}

int Mouse::getX()
{
	return this->curX;
}

int Mouse::getY()
{
	return this->curY;	
}
