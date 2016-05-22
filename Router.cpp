#include "Router.h"
#include "Mouse.h"

#include <stack>
#include <vector>

#define MAX_COUNT 9999

Matrix Router::tremauxRouting(const Matrix& map, const Matrix& moveCount, int curX, int curY)
{
	// moveCount==0 is higher value than 1
	// moveCount>=2 is equal wall, except crossroad
	// never back except dead-end road or cycle

	const int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	Matrix retMat;
	retMat.setInitValue(0);
	retMat.resize(map.getRows(), map.getCols());
	if(countAdjacentPath(map, curX, curY)==1 && moveCount[beginCurY][beginCurX]>=1){
		// dead-end road
		retMat[beginCurY][beginCurX] = 1;
	}
	else {
		std::vector< std::pair<int,int> > adj; // adjacent empty (x,y)
		for(int d=0; d<4; ++d){
			int tx = curX + dir[d][0];
			int ty = curY + dir[d][1];
			if(map.isIn(ty, tx) && map[ty][tx]==MAP_EMPTY)
				adj.push_back(std::make_pair(tx, ty));
		}
		int leastMcCondition = 1;
		bool cycle = true;
		for(int i=0; i<adj.size(); ++i){
			leastMcCondition = std::min(leastMcCondition, moveCount[adj[i].second][adj[i].first]);
			if(moveCount[adj[i].second][adj[i].first]!=1)
				cycle = false;
		}
		// one more check cycle
		if(cycle){
			for(int i=0; i<adj.size(); ++i){
				if(countAdjacentPath(map, adj[i].first, adj[i].second)==1){
					cycle = false;
					break;
				}
			}
		}

		if(cycle){
			retMat[beginCurY][beginCurX] = 1;
		}
		else {
			for(int i=0; i<adj.size(); ++i){
				if(moveCount[adj[i].second][adj[i].first]<=leastMcCondition)
					retMat[adj[i].second][adj[i].first] = 2;
				else if(countAdjacentPath(map, adj[i].first, adj[i].second)>2)
					retMat[adj[i].second][adj[i].first] = 1;
			}
			retMat[beginCurY][beginCurX] = 0;
		}
	}
	
	return retMat;
}

int Router::countAdjacentPath(const Matrix& map, int x, int y)
{
	const int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int count = 0;
	for(int d=0; d<4; ++d){
		int tx = x+dir[d][0];
		int ty = y+dir[d][1];
		if( map.isIn(ty,tx) && map[ty][tx]==MAP_EMPTY )
			++count;
	}
	return count;
}

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
	// return (x, y)

	// ADD : Matrix predictedValue = predictAlgo1 * predictAlgo2 * predictAlgo3;
	Matrix predictedValue;
	predictedValue = tremauxRouting(map, moveCount, curX, curY);
	std::pair<int, int> maxRowCol = predictedValue.getMaxRowCol();
	beginCurX = curX;
	beginCurY = curY;
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