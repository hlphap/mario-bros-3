#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CColorBox : public CGameObject
{
public:
	CColorBox();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};