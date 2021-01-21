#include "ItemEndGame.h"

CItemEndScence::CItemEndScence(float x, float y)
{
	type = TYPE::ITEM_END_GAME;
	isActive = true;
	SetPosition(x, y);
	SetState(ITEM_ENDSCENCE_STATE_NORMAL);
	this->posTextX = x - 38;
	this->posTextY = y - 76;
}

void CItemEndScence::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CItemEndScence::Render()
{
	if (state == ITEM_ENDSCENCE_STATE_NORMAL)
		ani = ITEM_ENDSCENCE_ANI;
	animation_set->at(ani)->Render(x,y);
}

void CItemEndScence::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_ENDSCENCE_STATE_NORMAL:
		vx = 0;
		vy = 0;
		break;
	case ITEM_ENDGAME_STATE_USED:
		isActive = false;
		break;
	}
}

void CItemEndScence::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}
