#include "MouseOfMazeSimulator.h"
#include "MazeGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main(void)
{
	MouseOfMazeSimulator simul;
	const string defaultFile = "defaultmap.txt";
	bool autoSimulation = true;
	int autoSimulRows = 50;
	int autoSimulCols = 50;
	int autoSimulPunch = 500; // <0 ... auto
	bool simulSimple = true;
	int simulInterval = 200;
	ostream* out = &(std::cout);
	string filename = "console";
	while(true){
		cout << "----------------------menu-------------------------\n";
		cout << "0 : exit program\n";
		cout << "1 : simulation\n";
		cout << "2 : generate maze\n";
		cout << "3 : settings\n";
		cout << "menu select : ";
		int menu=-1;
		cin >> menu;
		if(menu==0) {
			cout << "program is terminated successfully...\n";
			return 0;
		}
		else if(menu==1) {
			if(filename == "console")
				out = &(std::cout);
			else
				out = new ofstream(filename);
			if(autoSimulation) {
				MazeGenerator mg(autoSimulRows, autoSimulCols);
				mg.initialize();
				mg.run();
				mg.punch_a_maze(autoSimulPunch);
				mg.print_file(defaultFile.c_str());
				simul.readMap(defaultFile);
				simul.simulate(simulSimple, simulInterval, *out);
			}
			else {
				cout << "input maze file name : ";
				string fileName;
				cin >> fileName;
				if( simul.readMap(fileName) ){
					simul.simulate(simulSimple, simulInterval, *out);
				}
				else
					cout << " file open is failed!\n";
				cout << '\n';
			}
			if(out!=&(std::cout))
				delete out;
		}
		else if(menu==2) {
			int rows=50, cols=50, punch=0;
			cout << "maze rows and cols : ";
			cin >> rows >> cols;
			cout << "maze complexity(punch num, -1=auto) : ";
			cin >> punch;
			MazeGenerator mg(rows, cols);
			mg.punch_a_maze(punch);
			string outFile;
			cout << "maze file name : ";
			cin >> outFile;
			mg.print_file(outFile.c_str());
			cout << "maze file write complete.\n";
		}
		else if(menu==3) {
			cout << "set simulation auto(1=enable, 0=disable) : ";
			cin >> autoSimulation;
			if(autoSimulation){
				cout << "simulation rows, cols : ";
				cin >> autoSimulRows >> autoSimulCols;
				cout << "simulation complexity(punch num, -1=auto) : ";
				cin >> autoSimulPunch;
			}
			cout << "set simulation simple, only print result(1=enable, 0=disable) : ";
			cin >> simulSimple;
			if(!simulSimple){
				cout << "set simulation turns interval : ";
				cin >> simulInterval;
			}
			cout << "out file name(console=console) : ";
			cin >> filename;
		}
		else {
			cout << " menu select error!\n";
		}
	}
	return -1;
}