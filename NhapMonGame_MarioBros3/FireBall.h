#pragma once
#include "GameObject.h"
#include "Ground.h"
#include "Weapon.h"
#define BULLET_BBOX_WIDTH  8
#define BULLET_BBOX_HEIGHT 8

#define BULLET_FLY_SPEED_X	0.11f
#define	BULLET_FLY_SPEED_Y	0.11f
#define BULLET_GRAVITY		0.0004f
#define BULLET_AMOUNT		2
#define FIREBALL_STATE_FLY_BOTTOM_LEFT		100
#define FIREBALL_STATE_FLY_UPPER_LEFT		200	
#define FIREBALL_STATE_FLY_BOTTOM_RIGHT		300	
#define FIREBALL_STATE_FLY_UPPER_RIGHT		400
	

#define BULLET_STATE_EXPLOSIVE	999

#define BULLET_TIME_EXITS	3000
#define BULLET_TIME_EXPLOSIVE 800
#define TIME_DEFAULT		0
class CFireBall : public CGameObject
{
public:
	DWORD timeStartColl = TIME_DEFAULT;
	bool isExploding = false;
	CFireBall();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};