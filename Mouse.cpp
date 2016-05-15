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

	for(i = 0; i < 3; i++)
	{
		switch(i)
		{
		case 0:
			if( ( this->map.getValue(curX, curY + 1) == MAP_WALL))//벽일 때
			{
				this->map.setInitValue(MAP_WALL);
				this->map.resize(curX, curY + 1);

			}
			else//벽이 아닐떄
			{
				this->map.setInitValue(this->map.getValue(curX, curY + 1));
				this->map.resize(curX, curY + 1);
			}
			if(min.value > this->moveCount.getValue(curX, curY + 1))
			{
				min.value = this->moveCount.getValue(curX, curY + 1);
				min.x = curX;
				min.y = curY + 1;
			}

				min.value = this->moveCount.getValue(curX, curY + 1);
				min.x = curX;
				min.y = curY + 1;
			break;

		case 1:
			if(curX - 1 < 0)
			{
				printf("out of array\n");
				exit(1);
			}

			if((this->map.getValue(curX - 1, curY) == MAP_WALL))
			{
				this->map.setInitValue(MAP_WALL);
				this->map.resize(curX - 1, curY);
			}
			else
			{
				this->map.setInitValue(this->map.getValue(curX - 1, curY));
				this->map.resize(curX - 1, curY);
			}

			if(min.value > this->moveCount.getValue(curX - 1, curY))
			{
				min.value = this->moveCount.getValue(curX - 1, curY);
				min.x = curX - 1;
				min.y = curY;
			}
			else if(min.value == this->moveCount.getValue(curX - 1, curY))
			{
				srand(time(NULL));
				if(rand() % 2 == 1)
				{
					min.value = this->moveCount.getValue(curX - 1, curY);
					min.x = curX - 1;
					min.y = curY;
				}
				else
					min = min;				
			}
			break;

		case 2:
			if( (this->map.getValue(curX + 1, curY) == MAP_WALL))
			{
				this->map.setInitValue(MAP_WALL);
				this->map.resize(curX + 1, curY);
			}
			else
			{
				this->map.setInitValue(this->map.getValue(curX + 1, curY));
				this->map.resize(curX + 1, curY);
			}
			if(min.value > this->moveCount.getValue(curX + 1, curY))
			{
				min.value = this->moveCount.getValue(curX + 1, curY);
				min.x = curX + 1;
				min.y = curY;
			}
			else if(min.value == this->moveCount.getValue(curX + 1, curY))
			{
				srand(time(NULL));
				if(rand() % 2 == 1)
				{
					min.value = this->moveCount.getValue(curX + 1, curY);
					min.x = curX + 1;
					min.y = curY;
				}
				else
					min = min;			
			}
			break;

		case 3:
			if(curY - 1 < 0)
			{
				printf("out of array\n");
				exit(1);
			}

			if(this->map.getValue(curX, curY - 1) == MAP_WALL )
			{
				this->map.setInitValue(MAP_WALL);
				this->map.resize(curX, curY - 1);
			}
			else
			{
				this->map.setInitValue(this->map.getValue(curX, curY - 1));
				this->map.resize(curX, curY - 1);
			}
			if(min.value > this->moveCount.getValue(curX, curY - 1))
			{
				min.value = this->moveCount.getValue(curX, curY - 1);
				min.x = curX;
				min.y = curY - 1;
			}

			else if(min.value == this->moveCount.getValue(curX, curY - 1))
			{
				srand(time(NULL));
				if(rand() % 2 == 1)
				{
					min.value = this->moveCount.getValue(curX, curY - 1);
					min.x = curX;
					min.y = curY - 1;
				}
				else
					min = min;			
			}
			break;
		}
	}

	this->moveCount.setInitValue((this->moveCount.getValue(curX, curY))++);
	this->moveCount.resize(curX, curY);
	move(min.x, min.y);
}

void Mouse::move(int dx, int dy)
{
	
	this->curX = dx;
	this->curY = dy;
	this->mana++;
	this->health--;
	if(this->health < 1)
	{	
		printf("We failed to find the exit...\n");
		exit(100);
	}
	//when the mouse arrive at the eixt, need to know there is exit or not... how?

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