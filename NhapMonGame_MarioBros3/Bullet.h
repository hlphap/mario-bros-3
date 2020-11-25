#pragma once
#include "GameObject.h"
#include "Ground.h"
#include "Weapon.h"
#define BULLET_BBOX_WIDTH  8
#define BULLET_BBOX_HEIGHT 8

#define BULLET_FLY_SPEED_X	0.12f
#define	BULLET_FLY_SPEED_Y	0.16f
#define BULLET_GRAVITY		0.008f
#define BULLET_AMOUNT		2
#define BULLET_STATE_FLY_LEFT		100
#define BULLET_STATE_FLY_RIGHT		101	
#define BULLET_STATE_EXPLOSIVE	999

#define BULLET_TIME_EXITS	3000
#define BULLET_TIME_EXPLOSIVE 800
#define TIME_DEFAULT		0
class CBullet : public CWeapon
{
public:
	DWORD timeStartColl = TIME_DEFAULT;
	bool isExploding = false;
	CBullet();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};