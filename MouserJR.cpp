#include "MouseJR.h"

void MouseJR::init(const Matrix& map, const Matrix& moveCount, int curX, int curY)
{
	this->map = map;
	this->moveCount = moveCount;
	this->curX = curX;
	this->curY = curY;
}
void MouseJR::move(int dx, int dy)
{
	curX += dx;
	curY += dy;
	++moveCount[dx][dy];
}
void MouseJR::updateMap3x3(const Matrix& map)
{
	this->map.resize( map.getRows(), map.getCols() );
	for(int dy=-1; dy<=1; ++dy){
		for(int dx=-1; dx<=1; ++dx){
			if(map.isIn(curY+dy, curX+dx))
				this->map[curY+dy][curX+dx] = map[curY+dy][curX+dx];
		}
	}
}
int MouseJR::getX()
{
	return curX;
}
int MouseJR::getY()
{
	return curY;
}