#pragma once
#include "GameObject.h"
#include "Ground.h"
#include "Weapon.h"
#include "ImpactEffect.h"
#include "PieceBrickEffect.h"

#define TAIL_BBOX_WIDTH  8
#define TAIL_BBOX_HEIGHT 8

#define TAIL_SPEED_FLY		0.07f
#define TAIL_CAN_KILL		100
#define TAIL_CANNOT_KILL		101	

#define TIME_DEFAULT		0
class CTail : public CWeapon
{
public:
	CEffect* effect;
	DWORD timer = TIME_DEFAULT;
	bool canKill = false;
	bool isOneKill = false;
	static CTail* __instance;
public:
	CTail();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj, vector<LPGAMEOBJECT>* listEnemy, vector<LPGAMEOBJECT>* listItem,vector<LPGAMEOBJECT> *listEffect);
	static CTail* GetInstance();
};