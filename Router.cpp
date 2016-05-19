#include "Router.h"
#include "Mouse.h"

#include <stack>

#define MAX_COUNT 9999

// LNK2019 ���忡�� �߻����� ��� ���Ϸ� �ڵ� �̵�
//std::pair<int, int> routing(const Matrix& map, const Matrix& moveCount, int curX, int curY)
//{
//	// ADD : Matrix predictedValue = predictAlgo1 * predictAlgo2 * predictAlgo3;
//	Matrix predictedValue;
//	std::pair<int, int> maxRowCol = predictedValue.getMaxRowCol();
//	return std::make_pair(maxRowCol.second, maxRowCol.first);
//}

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
				//if( ( this->maze[curX + i][curY + j] == MAP_WALL))//���� ��
				//	map[curX + i][curY + j] = MAP_WALL;//access error�Ͼ�� ������...?
				//else//���� �ƴҋ�
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
	std::stack< std::pair<int, int> > begin, next; // next (x,y)
	Matrix mapClone = map;

	// find (x,y)
	begin.push(std::make_pair(curX, curY));
	mapClone[curX][curY] = beginCount;
	while(true){
		if(begin.empty()) return std::make_pair(0, 0); // cannot
		
		while(!begin.empty()) {
			std::pair<int, int> top = begin.top();
			if(top.first==x && top.second==y) break;
			begin.pop();
			for(int d=0; d<4; ++d) {
				int tx = top.first+dir[d][0];
				int ty = top.second+dir[d][1];
				if(mapClone.isIn(ty,tx) && mapClone[ty][tx]==MAP_EMPTY) {
					next.push(std::make_pair(tx,ty));
					mapClone[ty][tx] = mapClone[top.second][top.first]+1;
				}
			}
		}
		if(!begin.empty()) break;
		begin.swap(next);
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