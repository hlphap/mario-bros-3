#include "Enemy.h"

CEnemy::CEnemy()
{
	isActive = true;
	category = CATEGORY::ENEMY;
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ENEMY_GRAVITY * dt;
}
