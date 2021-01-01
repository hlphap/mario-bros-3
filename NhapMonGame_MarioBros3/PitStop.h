#pragma once
#include "GameObject.h"
class CPitStop :public CGameObject
{
public:
	//Flag Go
	bool isAllowLeft = false;
	bool isAllowRight = false;
	bool isAllowUp = false;
	bool isAllowDown = false;
public:
	CPitStop(bool isLeft, bool isRight, bool isUp, bool isDown);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

