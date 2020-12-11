#include "ImpactEffect.h"

CImpactEffect::CImpactEffect(float x, float y)
{
	type = TYPE::IMPACT_EFFECT;
	SetPosition(x, y);
}

void CImpactEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - timestartEffect >= TIME_EXITS_EFFECT && timestartEffect != TIME_DEFAULT)
	{
		isActive = false;
	}
}

void CImpactEffect::Render()
{
	animation_set->at(EFFECT_ANI_IMPACT_BY_TAIL)->Render(x,y);
}

void CImpactEffect::SetState(int state)
{
}

void CImpactEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
