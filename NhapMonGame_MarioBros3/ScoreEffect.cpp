#include "ScoreEffect.h"

CScoreEffect::CScoreEffect(float x, float y)
{
	vy = -0.02;
	SetPosition(x, y);
}

void CScoreEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - timestartEffect >= TIME_EXITS_EFFECT && timestartEffect != TIME_DEFAULT)
	{
		isActive = false;
	}
	y += dy;
}

void CScoreEffect::Render()
{
	switch (score)
	{
	case 100:
		ani = EFFECT_ANI_POINT_100;
		break;
	case 200:
		ani = EFFECT_ANI_POINT_200;
		break;
	case 400:
		ani = EFFECT_ANI_POINT_400;
		break;
	case 800:
		ani = EFFECT_ANI_POINT_800;
		break;
	case 1000:
		ani = EFFECT_ANI_POINT_1000;
		break;
	case 2000:
		ani = EFFECT_ANI_POINT_2000;
		break;
	case 4000:
		ani = EFFECT_ANI_POINT_4000;
		break;
	case 8000:
		ani = EFFECT_ANI_POINT_8000;
		break;
	default:
		ani = -1;
	}
	if (ani != -1)
		animation_set->at(ani)->Render(x, y);
}

void CScoreEffect::SetState(int state)
{
}

void CScoreEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
