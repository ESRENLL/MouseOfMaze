#include "MouseJR.h"

void MouseJR::init(const Matrix& map, int curX, int curY)
{
	this->map = map;
	this->curX = curX;
	this->curY = curY;
	++moveCount[curX][curY];
}
void MouseJR::move(int dx, int dy)
{
	curX += dx;
	curY += dy;
	++moveCount[dx][dy];
}
int MouseJR::getX()
{
	return curX;
}
int MouseJR::getY()
{
	return curY;
}