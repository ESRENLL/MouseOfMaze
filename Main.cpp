#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool readMaze(Matrix& maze); // 미로를 읽어 maze에 저장하는 함수. 파일명은 stdin

int main(void)
{
	Matrix maze;
	while( !readMaze(maze) );

	cout << "rows, cols : " << maze.getRows() << ", " << maze.getCols() << endl;
	for(int row=0; row<maze.getRows(); ++row){
		for(int col=0; col<maze.getCols(); ++col)
			cout << maze[row][col] << ' ';
		cout << '\n';
	}

	return 0;
}


bool readMaze(Matrix& maze)
{
	maze.resize(0, 0);
	cout << "input file name: ";
	string inputFile;
	cin >> inputFile;
	ifstream ifs(inputFile);
	if(!ifs.is_open()){
		cout << "file open error! exit program...\n";
		return false;
	}
	int curRow=0, curCol=0;
	string line;
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