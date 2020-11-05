#pragma once
#include "GameObject.h"
#include "Mario.h"

#define ENEMY_GRAVITY_JUMP 0.001f
#define ENEMY_GRAVITY 0.005f
#define ENEMY_JUMP_SPEED 0.32f
#define ENEMY_SPEED 0.12f

class CEnemy : public CGameObject
{
public:
	CMario* mario;
	CEnemy();
};