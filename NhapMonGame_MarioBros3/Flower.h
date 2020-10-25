#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH  16
#define FLOWER_BBOX_HEIGHT 16

class CFlower : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};