/*@author sikuE
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<time.h>
using namespace std;

//---------------------------------------class-------------------------------------------------------------
class Maze {
private:
	int rows;
	int cols;
	vector<vector<bool>> maze;

public:
	Maze() {
		rows = 0;
		cols = 0;
	}
	Maze(int row, int col) {
		rows = row;
		cols = col;
	}
	void setSize(int row, int col);
	void initialize();
	void print_console();
	void print_file(char* fileName);
	void run();
	void punch_a_maze();
};
//--------------------------------------------main-----------------------------------------------------
int main() {
	Maze maze(25, 25);
	maze.initialize();
	maze.run();
	maze.punch_a_maze();
	maze.print_console();
	maze.print_file("output.txt");
}
//--------------------------------------------method-------------------------------------------------
/*set Maze size
*@param row rows
*@param col cols
*/
void Maze::setSize(int row, int col) {
	rows = row;
	cols = col;
}
/*initialize Maze
*ture is wall, and false is empty area.
*/
void Maze::initialize() {
	//create rows*cols matrix. 
	maze.resize(rows);
	for (int i = 0; i < rows; i++) 
		maze[i].resize(cols);
	

	for (int i = 0; i < rows; i++) {// fill maze with wall
		for (int j = 0; j < cols; j++)
			maze[i][j] = true;
	}
}
/*print maze on console
*/
void Maze::print_console() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j])
				cout << '#' << ' ';
			else
				cout <<". ";
		}
		cout << endl;
	}
}
/*print maze on file
@param fileName file directory which you want to print
*/
void Maze::print_file(char* fileName) {
	ofstream fout;
	fout.open(fileName);
	if (!fout.is_open())
		return;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fout << (int)maze[i][j] << ' ';
		}
		fout << endl;
	}
	fout.close();
}
/*make maze
*/
void Maze::run() {
	srand(time(NULL));
	//initialize maze
	if (rows % 2 == 0)
		rows++;
	if (cols % 2 == 0)
		cols++;
	initialize();

	//create cells
	//cell is 2*2 squre
	vector<vector<vector<bool>>> cell;
	int cell_row = rows / 2;
	int cell_col = cols / 2;
	cell.resize(cell_row);
	for (int i = 0; i < cell_row; i++) 
		cell[i].resize(cell_col);
	for (int i = 0; i < cell_row; i++)
		for (int j = 0; j < cell_col; j++)
			/*cell[i][j][0] is 0,0
			cell[i][j][1] is 0,1
			cell[i][j][2] is 1,0
			cell[i][j][3] is 1,1
			cell[i][j][4] is information that you visited
			*/
			cell[i][j].resize(5);	

	//initialize cell
	for (int i = 0; i < cell_row; i++)
		for (int j = 0; j < cell_col; j++) {
			for (int k = 0; k < 4; k++)
				cell[i][j][k] = true;
			cell[i][j][4] = false;
		}
	//set starting row, col
	int row = 0;
	int col = 0;
	//create history
	list<pair<int,int>> history;
	history.push_back(make_pair(row, col));
	while (history.size()) {	// end if can't backtrack
		cell[row][col][4] = true;	//we visited this cell(row*col)
		char check[4];				//where is open?
		int check_num = 0;
		if (col > 0 && cell[row][col - 1][4] == false) {
			check[check_num] = 0;	//left
			check_num++;
		}
		if (row > 0 && cell[row - 1][col][4] == false) {
			check[check_num] = 1;	//up
			check_num++;
		}
		if (col < cell_col-1 && cell[row][col + 1][4] == false) {
			check[check_num] = 2;	//right
			check_num++;
		}
		if (row < cell_row-1 && cell[row + 1][col][4] == false) {
			check[check_num] = 3;//down
			check_num++;
		}

		if (check_num != 0) {	//go if you can
			history.push_back(make_pair(row, col));	// stack where you are on history
			char move_direction = check[rand() % check_num];	//random select direction
			cell[row][col][3] = false;
			switch (move_direction) {
			case 0:	//left
				cell[row][col][2] = false;
				col--;
				cell[row][col][3] = false;
				break;

			case 1:	//up
				cell[row][col][1] = false;
				row--;
				cell[row][col][3] = false;
				break;
			case 2:	//right
				cell[row][col][3] = false;
				col++;
				cell[row][col][2] = false;
				break;
			case 3:	//down
				cell[row][col][3] = false;
				row++;
				cell[row][col][1] = false;
				break;
			}
		}
		else {//backtrack
			row = history.back().first;
			col = history.back().second;
			history.pop_back();
		}
		/*//debug
		for (int i = 0; i < cell_row; i++) {
			for (int j = 0; j < cell_col; j++) {
				cout << cell[i][j][4] << " ";
			}
			cout << endl;
		}
		cout << endl;
		*/
	}
	//write on maze
	for (int i = 0; i < cell_row; i++) {
		for (int j = 0; j < cell_col; j++) {
			if (!cell[i][j][0])
				maze[i * 2][j * 2] = false;
			if (!cell[i][j][1])
				maze[i * 2][j * 2+1] = false;
			if (!cell[i][j][2])
				maze[i * 2+1][j * 2] = false;
			if (!cell[i][j][3])
				maze[i * 2+1][j * 2+1] = false;
		}
	}
	maze[0][1] = false;	//starting point
	//create end point
	int end_floor = rand() % 4;	// direction of end point(0: left, 1: up, 2: right, 3: down)
	bool end = false;	// if make end point?
	while (!end) {
		int temp;			// randomly point 
		switch (end_floor) {
		case 0:
			temp = rand() % rows;
			if (!maze[temp][1]) {
				maze[temp][0] = false;
				end = true;
			}
			break;
		case 1:
			temp = rand() % cols;
			if (!maze[1][temp]) {
				maze[0][temp] = false;
				end = true;
			}
			break;
		case 2:
			temp = rand() % rows;
			if (!maze[temp][cols-2]) {
				maze[temp][cols-1] = false;
				end = true;
			}
			break;
		case 3:
			temp = rand() % cols;
			if (!maze[rows-2][temp]) {
				maze[rows-1][temp] = false;
				end = true;
			}
			break;
		}
	}
}
/*punch a maze
*/
void Maze::punch_a_maze() {
	srand(time(NULL));
	int num = 2*sqrt(rows)*sqrt(cols);	// punch times
	for (int i = 0; i < num; i++) {
		int row = -1;
		int col = -1;
		while (row < 1 || row > rows - 2) {
			row = rand() % rows;
		}
		while (col < 1 || col > cols - 2) {
			col = rand() % cols;
		}
		maze[row][col] = false;
	}
}
