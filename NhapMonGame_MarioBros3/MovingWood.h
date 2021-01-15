#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define MARIO_GRAVITY	 0.00045f


#define MOVING_WOOD_STATE_MOVING_HORIZONTAL	100
#define MOVING_WOOD_STATE_FALLING			200

class CMovingWood : public CGameObject
{
public:
	float vyMax;
public:
	CMovingWood();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj = NULL);
	void SetState(int state);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};