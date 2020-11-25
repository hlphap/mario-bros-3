#pragma once
#include "GameObject.h"
#include "Ground.h"
#include "Weapon.h"
#define TAIL_BBOX_WIDTH  8
#define TAIL_BBOX_HEIGHT 8

#define TAIL_SPEED_FLY		0.07f
#define TAIL_CAN_KILL		100
#define TAIL_CANNOT_KILL		101	

#define TIME_DEFAULT		0
class CTail : public CWeapon
{
public:

	DWORD timer = TIME_DEFAULT;
	bool canKill = false;
	static CTail* __instance;

	CTail();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	static CTail* GetInstance();
};