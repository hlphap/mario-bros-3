#include "BackGroundIntro.h"

CBackGroundIntro::CBackGroundIntro()
{
	isActive = true;
	this->type = TYPE::BACKGROUNDINTRO;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(20);
	SetAnimationSet(ani_set);
	vy = 0.3f;
}

CBackGroundIntro::~CBackGroundIntro()
{
}

void CBackGroundIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* staticObj)
{
	CGameObject::Update(dt);
	if (y < 8)
	{
		x += dx;
		y += dy;
	}
}

void CBackGroundIntro::Render()
{
	animation_set->at(2)->Render(x, y);
}

void CBackGroundIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b;
}
