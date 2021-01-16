#pragma once
#include "GameObject.h"
#include <unordered_set>
class CCell
{
public:
	int posX, posY;
	RECT bbox;
	unordered_set<LPGAMEOBJECT> movingObject;
	unordered_set<LPGAMEOBJECT> staticObjects;
	CCell(int x, int y)
	{
		this->posX = x;
		this->posY = y;
		movingObject.clear();
		staticObjects.clear();
	}
	RECT GetBBox() {
		return bbox;
	}
	~CCell() {};
};