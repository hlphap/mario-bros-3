#pragma once
#include "GameObject.h"

#define BOUNDARYBRICK_BBOX_WEIGHT  2
#define BOUNDARYBRICK_BBOX_HEIGHT 30

class CBoundaryBrick : public CGameObject
{
public:
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};