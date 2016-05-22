#include "MouseOfMazeSimulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main(void)
{
	MouseOfMazeSimulator simul;
	while(true){
		cout << "input maze file name : ";
		string fileName;
		cin >> fileName;
		if( simul.readMap(fileName) ){
			//simul.simulate(false, true, 200);
			simul.simulate(false);
		}
		else
			cout << " file open is failed!\n";
		cout << '\n';
	}
	return -1;
}