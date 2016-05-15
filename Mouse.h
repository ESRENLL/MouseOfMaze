#pragma once

#include "Matrix.h"
#include "MouseJR.h"

class Mouse {
protected:
	Matrix map; // enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };
	Matrix moveCount; // 이동한 횟수(default 0)
	int curX;
	int curY;
	int health;
	int mana;
public:
	Mouse(int health) : map(), curX(1), curY(0), health(health), mana(0) {}
	~Mouse() {}
	void routing(); // 길찾기(스캔 고려x), move
	void consumeMana(); // 스캔 장소 고려, 스캔
	void move(int dx, int dy); // 이동 후 맵(+moveCount, health, mana, x, y) 갱신
	void scan(int x, int y); // 스캔 후 맵 및 마나 갱신
	int getX(); // 자신의 현재위치 x를 반환
	int getY(); // 자신의 현재위치 y를 반환
};