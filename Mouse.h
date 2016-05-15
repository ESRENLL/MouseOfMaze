#pragma once

#include "Matrix.h"
#include "MouseJR.h"

class Mouse {
protected:
	Matrix map; // enum MAPSTATE { MAP_EMPTY=0, MAP_WALL, MAP_FOG };
	Matrix moveCount; // �̵��� Ƚ��(default 0)
	int curX;
	int curY;
	int health;
	int mana;
public:
	Mouse(int health) : map(), curX(1), curY(0), health(health), mana(0) {}
	~Mouse() {}
	void routing(); // ��ã��(��ĵ ���x), move
	void consumeMana(); // ��ĵ ��� ���, ��ĵ
	void move(int dx, int dy); // �̵� �� ��(+moveCount, health, mana, x, y) ����
	void scan(int x, int y); // ��ĵ �� �� �� ���� ����
	int getX(); // �ڽ��� ������ġ x�� ��ȯ
	int getY(); // �ڽ��� ������ġ y�� ��ȯ
};