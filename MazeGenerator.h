#pragma once

/*@author sikuE
*/

#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;

class MazeGenerator {
private:
	int rows;
	int cols;
	vector<vector<bool>> maze;

public:
	MazeGenerator() {
		srand(time(NULL));
		rows = 0;
		cols = 0;
	}
	MazeGenerator(int row, int col) {
		rows = row;
		cols = col;
	}
	void setSize(int row, int col);
	void initialize();
	void print_console();
	void print_file(const char* fileName);
	void run();
	void punch_a_maze(int num=-1);
};