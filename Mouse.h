#pragma once

#include "Matrix.h"
#include "Router.h"
#include "MouseJR.h"

enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };

class Mouse {
private:
	const Matrix maze;
	Matrix map; // enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };
	Matrix moveCount; // 이동한 횟수(default 0)
	Router router;
	//MouseJR jr;
	int curX;
	int curY;
	int health;
	int mana;
public:
	Mouse(const Matrix& maze) : maze(maze), map(), curX(1), curY(0), health(2*maze.getRows()*maze.getCols()), mana(0) {
		map.setInitValue(MAP_FOG);
		map.resize(2, 3);
		for(int row=0; row<2; ++row){
			for(int col=0; col<3; ++col)
				map[row][col] = maze[row][col];
		}
	}
	~Mouse() {}
	void useTurn();
	void move(int dx, int dy); // 이동 후 맵(+moveCount, health, mana, x, y) 갱신
	void scan(int x, int y); // 스캔 후 맵 및 마나 갱신
	int getX(); // 자신의 현재위치 x를 반환
	int getY(); // 자신의 현재위치 y를 반환
	bool isEscapeMaze(); // 미로 탈출 여부 반환
};
