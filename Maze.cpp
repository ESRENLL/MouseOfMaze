#include<iostream>
#include<vector>
#include<list>
#include<time.h>
using namespace std;

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
	void initialize();
	void print_console();
	void run();
};

int main() {
	Maze maze(25, 25);
	maze.initialize();
	maze.run();
	maze.print_console();
}

void Maze::initialize() {
	maze.resize(rows);
	for (int i = 0; i < rows; i++) 
		maze[i].resize(cols);
	

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)

			maze[i][j] = true;
	}
}

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
	while (history.size()) {
		cell[row][col][4] = true;
		char check[4];
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

		if (check_num != 0) {
			history.push_back(make_pair(row, col));
			char move_direction = check[rand() % check_num];
			cell[row][col][3] = false;
			switch (move_direction) {
			case 0:
				cell[row][col][2] = false;
				col--;
				cell[row][col][3] = false;
				break;

			case 1:
				cell[row][col][1] = false;
				row--;
				cell[row][col][3] = false;
				break;
			case 2:
				cell[row][col][3] = false;
				col++;
				cell[row][col][2] = false;
				break;
			case 3:
				cell[row][col][3] = false;
				row++;
				cell[row][col][1] = false;
				break;
			}
		}
		else {
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