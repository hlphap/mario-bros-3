#include "OneUpEffect.h"

COneUpEffect::COneUpEffect(float x, float y)
{
	vy = -0.02;
	SetPosition(x, y);
}

void COneUpEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - timestartEffect >= TIME_EXITS_EFFECT && timestartEffect != TIME_DEFAULT)
	{
		isActive = false;
	}
	y += dy;
}

void COneUpEffect::Render()
{
	animation_set->at(EFFECT_ANI_ONE_UP)->Render(x, y);
}

void COneUpEffect::SetState(int state)
{
}

void COneUpEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	return;
}
