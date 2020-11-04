#pragma once
#include "GameObject.h"
#include "Ground.h"

#define TAIL_BBOX_WIDTH  16		
#define TAIL_BBOX_HEIGHT 8

#define TAIL_SPEED_FLY		0.12f
#define TAIL_CAN_KILL		100
#define TAIL_CANNOT_KILL		101	

#define TIME_DEFAUL		0
class CTail : public CGameObject
{
public:

	DWORD timer = TIME_DEFAUL;
	bool canKill = false;

	CTail();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};