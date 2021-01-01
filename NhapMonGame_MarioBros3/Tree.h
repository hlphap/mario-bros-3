#pragma once
#include "GameObject.h"
class CTree :public CGameObject
{
public:
public:
	CTree();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

