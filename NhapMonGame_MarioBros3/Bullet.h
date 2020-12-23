#pragma once
#include "GameObject.h"
#include "Ground.h"
#include "Weapon.h"
#include "ExplosiveEffect.h"
#define BULLET_BBOX_WIDTH  8
#define BULLET_BBOX_HEIGHT 8

#define BULLET_FLY_SPEED_X	0.1f
#define	BULLET_FLY_SPEED_Y	0.1f
#define BULLET_GRAVITY		0.0004f
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
	CEffect* effect;
public:

	CBullet();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj, vector<LPGAMEOBJECT>* listEnemy, vector<LPGAMEOBJECT>* listEffect);
};