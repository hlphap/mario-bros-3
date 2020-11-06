#pragma once
#include "Enemy.h"
#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_GRAVITY		0.0006f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_JUMP_DEFLECT_SPEED	0.2f
#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1

class CGoomba : public CEnemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	bool isKillByWeapon = false;
	CGoomba(CMario *m);
	void SetState(int state);
};