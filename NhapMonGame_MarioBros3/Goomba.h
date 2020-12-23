#pragma once
#include "Enemy.h"
#include "GoombaGeneral.h"
#define GOOMBA_SPEED_MOVE	0.03f
#define GOOMBA_SPEED_WHEN_DIE 0.02f
#define GOOMBA_GRAVITY		0.0006f
#define GOOMBA_SPEED_BOUNCE	0.2f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9
#define GOOMBA_HAVE_WING_BBOX_HEIGHT 19
#define GOOMBA_HAVE_WING_BBOX_WIDTH 20

#define GOOMBA_STATE_MOVE 100
#define GOOMBA_STATE_DIE 200


class CGoomba : public CEnemy
{
public:
	CGoombaGeneral* goombaGeneral;
	int level;
	int typeColor;
	bool isMoving = true;
	bool isAllowJump = true;
	int numJump = 0;
	bool isFlying = false;
	DWORD timeStartMove = TIME_DEFAULT;
public:
	CGoomba(CMario* m, int type, int level);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};