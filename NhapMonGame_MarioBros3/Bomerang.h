#pragma once
#include "GameObject.h"
#include "Mario.h"

#define BOMERANG_BBOX_WIDTH 16
#define BOMERANG_BBOX_HEIGHT 16

#define BOOMERANG_STATE_MOVING_ATTACK 100
#define BOOMERANG_STATE_DOWN_ATTACK 200
#define BOOMERANG_STATE_MOVING_DOWN_ATTACK 300
#define BOOMERANG_STATE_MOVING_RETURN 400


class CBomerang :public CGameObject
{
public:

	float maxX;
	float minX;
	float minY;
	float maxY;
public:
	CBomerang(int nx,  float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void SetState(int state);
	~CBomerang() {};
};

