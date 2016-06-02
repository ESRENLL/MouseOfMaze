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
if(not mana >= 10){
		return;
	}
	mana -= 10;

	bool flagE = false;	// flag about finding exit point
	bool flagR = false; // if end searching about rows
	bool flagC = false;
	// scan point
	int prevRow=1;
	int row=1;
	int prevCol=0;
	int col=0;
	while(true){
		if(flagE){	// if found exit
			srand(time(NULL));
			while(map[row][col] != MAP_FOG){
				row = rand() % (map.getRows() - 3) + 1;
				col = rand() % (map.getCols() - 3) + 1;
			}
		}
		else{ // if didnt found exit
			try{
				if(!flagR && !flagC) // map's left side
					row++;
				else if(flagR && !flagC)	//map's down side
					col++;
				else if(flagR && flagC)	// map's right side
					row--;
				else
					col--;	//map's up side

				if(map[row][col] == MAP_FOG && map[prevRow][prevCol] == MAP_FOG)
					break;
				prevRow = row;
				prevCol = col;
				if(flagR && row == 0)
					flagR = false;
				if(!flagR && row == maze.getRows()-1)
					flagR = true;
				if(!flagC && col == maze.getCols()-1)
					flagC = true;
				if(map[row][col] == MAP_EMPTY)
					flagE = true;
			}
			catch(const std::out_of_range& oor){ // if point is out of range
					if(row > map.getRows()){
						int resizeRows = std::max(map.getRows(), row+1);
						int resizeCols = std::max(map.getCols(), col);
						map.resize(resizeRows, resizeCols);
					}
					if (col > map.getCols()) {
						int resizeRows = std::max(map.getRows(), row);
						int resizeCols = std::max(map.getCols(), col + 1);
						map.resize(resizeRows, resizeCols);
					}
			}
		}
	}
	/*/
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
	*/
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
	return curCol==0 || (curRow==0 && curCol!=1) || curCol==maze.getCols()-1 || curRow==maze.getRows()-1;
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
