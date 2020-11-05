#pragma once
#include "Enemy.h"
#include "BoundaryBrick.h"

#define KOOPAS_WALKING_SPEED 0.03f
#define KOOPAS_RUNNING_WHEN_KICKED 0.15f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_SLEEP 6

#define KOOPAS_STATE_MOVING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_SLEEP 300

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_SHELL_IDLE 2
#define KOOPAS_ANI_SHELL_HEALTH 3
#define KOOPAS_ANI_SHELL_MOVE 4
#define KOOPAS_ANI_SHELL_OVERTURNED_IDLE 5
#define KOOPAS_ANI_SHELL_OVERTURNED_MOVE 10
#define KOOPAS_ANI_SHELL_OVERTURNED_HEALTH 11


class CKoopas : public CEnemy
{
public:
	bool isSleeping = false;
	bool isMove = true;
	bool isKicked = false;
	bool isHeld = false;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
    void Render();

public:
	CKoopas(CMario *m);
	void SetState(int state);
};