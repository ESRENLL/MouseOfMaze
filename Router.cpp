#include "Router.h"
#include "Mouse.h"

#include <stack>

#define MAX_COUNT 9999

Matrix Router::randomRouting(const Matrix& map, int curX, int curY)
{
	Matrix retMat;
	retMat.setInitValue(0);
	const int rows = map.getRows();
	const int cols = map.getCols();
	retMat.resize(rows, cols);
	for(int row=0; row<rows; ++row){
		for(int col=0; col<cols; ++col){
			if(map[row][col] == MAP_EMPTY && (row!=curY || col!=curX))
				retMat[row][col] = rand()%99+1;
		}
	}
	return retMat;
}

std::pair<int, int> Router::routing(const Matrix& map, const Matrix& moveCount, int curX, int curY)
{
	// ADD : Matrix predictedValue = predictAlgo1 * predictAlgo2 * predictAlgo3;
	Matrix predictedValue;
	predictedValue = randomRouting(map, curX, curY);
	std::pair<int, int> maxRowCol = predictedValue.getMaxRowCol();
	return std::make_pair(maxRowCol.second, maxRowCol.first);
}

//define where is conjuction
std::pair<int, int> Router::simpleRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY)
{
	typedef struct possiblePath
	{
		int x;
		int y;
		int value;
	}path;
	int i, j;
	int num = 0;
	path min;
	min.value = MAX_COUNT;

	for(i = -1; i <= 1; i++)
	{
		for(j = -1; j <= 1; j++)
		{
			if( i + j == 1 || i + j == -1)
			{
				//if( ( this->maze[curX + i][curY + j] == MAP_WALL))//벽일 때
				//	map[curX + i][curY + j] = MAP_WALL;//access error일어나지 않을까...?
				//else//벽이 아닐떄
				//	map[curX + i][curY + j] = maze[curX + i][curY + j];//input maze data to map array
				if(min.value > moveCount[curY + i][curX + j])//decide which block has minimum value
				{
					min.value = moveCount[curY + i][curX + j];
					min.x = curX + i;
					min.y = curY + j;
				}
				else if(min.value == map[curY + i][curX + j])//if there is 2 minimum value in the 4 block
				{
					//srand(time(NULL)); move to constructor
					if(rand() % 2 == 1)//make 0 or 1 to decide randomly blocks which have same value 
					{
						min.value = moveCount[curY + i][curX + j];
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


	//this->moveCount.setInitValue((this->moveCount.getValue(curX, curY))++);
	//this->moveCount.resize(curX, curY);
	//++moveCount[min.y][min.x];
	//move(min.x, min.y);
	return std::make_pair(min.x, min.y);
}

std::pair<int, int> Router::howToGo(const Matrix& map, int curX, int curY, int x, int y)
{
	// return dx, dy

	if(curX==x && curY==y) return std::make_pair(0,0);

	const int beginCount = 10000;
	const int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // direction, (x,y)
	std::stack< std::pair<int, int> > before, next; // next (x,y)
	Matrix mapClone = map;

	// find (x,y)
	before.push(std::make_pair(curX, curY));
	mapClone[curY][curX] = beginCount;
	while(true){
		if(before.empty()) return std::make_pair(0, 0); // cannot
		
		while(!before.empty()) {
			std::pair<int, int> top = before.top();
			if(top.first==x && top.second==y) break;
			before.pop();
			for(int d=0; d<4; ++d) {
				int tx = top.first+dir[d][0];
				int ty = top.second+dir[d][1];
				if(mapClone.isIn(ty,tx) && mapClone[ty][tx]==MAP_EMPTY) {
					next.push(std::make_pair(tx,ty));
					mapClone[ty][tx] = mapClone[top.second][top.first]+1;
				}
			}
		}
		if(!before.empty()) break;
		if(next.empty()) return std::make_pair(0,0);
		before.swap(next);
	}
	
	// back from (x,y)
	int backX = x;
	int backY = y;
	while(abs(backX-curX)+abs(backY-curY)!=1) {
		for(int d=0; d<4; ++d) {
			int tx = backX+dir[d][0];
			int ty = backY+dir[d][1];
			if(mapClone.isIn(ty,tx) && mapClone[ty][tx]==mapClone[backY][backX]-1) {
				backX = tx;
				backY = ty;
				break;
			}
		}
	}
	return std::make_pair(backX-curX, backY-curY);
}