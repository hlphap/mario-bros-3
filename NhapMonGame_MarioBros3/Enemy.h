#pragma once
#include "GameObject.h"
#include "Mario.h"

#define ENEMY_GRAVITY_JUMP 0.001f
#define ENEMY_GRAVITY 0.0005f
#define ENEMY_JUMP_SPEED 0.32f
#define ENEMY_SPEED 0.12f

class CEnemy : public CGameObject
{
public:
	CMario* player;
	bool isKillByWeapon = false;
	DWORD timeStartDie = TIME_DEFAULT;
public:
	CEnemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};