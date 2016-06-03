#include "MouseOfMazeSimulator.h"
#include "Mouse.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <ctime>

bool MouseOfMazeSimulator::readMap(std::string fileName)
{
	maze.resize(0, 0);
	std::ifstream ifs(fileName);
	if(!ifs.is_open())
		return false;
	int curRow=0, curCol=0;
	std::string line;
	while( getline(ifs,line) ) {
		curCol = 0;
		maze.resize(curRow+1, maze.getCols());
		for(int i=0; i<line.size(); ++i){
			if(line[i]=='0' || line[i]=='1'){
				if(maze.getCols() <= curCol)
					maze.resize(curRow+1, curCol+1);
				maze[curRow][curCol] = line[i]-'0';
				++curCol;
			}
		}
		++curRow;
	}
	ifs.close();
	return true;
}
void MouseOfMazeSimulator::simulate(bool simple, int observeInterval)
{
	std::cout << " -- simulate start -- \n";
	clock_t beginClock = clock();
	Mouse mouse(maze);
	int elapsedTurn = 0;
	while(mouse.getHealth()>0 && !mouse.isEscapeMaze()){
		if(!simple){
			mouse.printMap();
			std::cout << '\n';
			Sleep(observeInterval);
		}
		mouse.useTurn();
		++elapsedTurn;
	}
	std::cout << " -- simulate end --, simulated time : " << clock()-beginClock << "(ms)\n";

	std::cout << '\n';
	mouse.printMap();
	if(mouse.isEscapeMaze())
		std::cout << " Mouse is escaped maze!\n";
	else
		std::cout << " Mouse is dead...\n";
	std::cout << " Elapsed turn : " <<  elapsedTurn << '\n';
	std::cout << " Remain health : " << mouse.getHealth() << '\n';
}
Matrix MouseOfMazeSimulator::getMaze()
{
	return maze;
}