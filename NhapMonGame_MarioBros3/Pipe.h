#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CPipe : public CGameObject
{
public:
	bool isSpecial = false;
	bool isPullMario;
	bool isInMainMap;

public:
	CPipe(bool special, bool where, bool uses);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};