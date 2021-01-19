#include "SelectionEffect.h"

CSelectionEffect::CSelectionEffect(CMario *mario, float x, float y)
{
	this->mario = mario;
	SetPosition(x, y);
}

void CSelectionEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj)
{
	location = mario->isLocationSelect;
	if (location)
	{
		SetPosition(70, 152);
	}
	else
	{
		SetPosition(70, 168);
	}
}

void CSelectionEffect::SetState(int state)
{
}

void CSelectionEffect::Render()
{
	animation_set->at(15)->Render(x, y);
}

void CSelectionEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
