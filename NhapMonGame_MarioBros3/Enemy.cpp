#include "Enemy.h"

CEnemy::CEnemy()
{
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ENEMY_GRAVITY * dt;
}
