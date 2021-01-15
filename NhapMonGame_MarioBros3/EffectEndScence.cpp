#include "EffectEndScence.h"

CEffectEndScence::CEffectEndScence(float x, float y)
{
	type = TYPE::ENDSCENCE_EFFECT;
	SetPosition(x, y);
	vy = -0.2f;
}

void CEffectEndScence::Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj)
{
	CGameObject::Update(dt, listMapObj);
	y += dy;
	
}

void CEffectEndScence::SetState(int state)
{
	CGameObject::SetState(state);
}

void CEffectEndScence::Render()
{
	switch (typeEffect)
	{
	case 1:
		ani = 12;
		break;
	case 2:
		ani = 13;
		break;
	case 3:
		ani = 14;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CEffectEndScence::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	return;
}

