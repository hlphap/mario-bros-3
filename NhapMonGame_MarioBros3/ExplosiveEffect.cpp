#include "ExplosiveEffect.h"

CExplosiveEffect::CExplosiveEffect(float x, float y)
{
	type = TYPE::EXPLOSIVE_EFFECT;
	SetPosition(x, y);
}

void CExplosiveEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	if (GetTickCount() - timestartEffect >= TIME_EXITS_EFFECT && timestartEffect != TIME_DEFAULT)
	{
		isActive = false;
	}
}

void CExplosiveEffect::Render()
{

	animation_set->at(EFFECT_ANI_BULLET_EXPLOSIVE)->Render(x, y);
}

void CExplosiveEffect::SetState(int state)
{
}

void CExplosiveEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
