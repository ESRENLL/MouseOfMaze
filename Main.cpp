#include "MouseOfMazeSimulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

bool readMaze(Matrix& maze); // �̷θ� �о� maze�� �����ϴ� �Լ�. ���ϸ��� stdin

int main(void)
{
	MouseOfMazeSimulator simul;
	while(true){
		cout << "input maze file name : ";
		string fileName;
		cin >> fileName;
		if( simul.readMap(fileName) ){
			//simul.simulate(false, true, 300);
			simul.simulate();
		}
		else
			cout << " file open is failed!\n";
	}
	return -1;
}