#include "Enemy.h"

CEnemy::CEnemy()
{
	isActive = true;
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ENEMY_GRAVITY * dt;
}
