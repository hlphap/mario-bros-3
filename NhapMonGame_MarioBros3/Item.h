#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

class CItem : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};