#pragma once
#include "Enemy.h"
#define GOOMBA_SPEED_MOVE	0.05f
#define GOOMBA_SPEED_WHEN_DIE 0.02f
#define GOOMBA_GRAVITY		0.0006f
#define GOOMBA_SPEED_BOUNCE	0.2f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_MOVE 100
#define GOOMBA_STATE_DIE 200


#define GOOMBA_ANI_MOVING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_DIE_REVERSE 2

class CGoomba : public CEnemy
{
public:
	CGoomba(CMario* m);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};