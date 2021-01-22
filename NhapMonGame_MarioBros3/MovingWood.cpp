#include "MovingWood.h"

CMovingWood::CMovingWood()
{
	this->type = TYPE::MOVINGWOOD;
	category = CATEGORY::GROUND;
	isActive = true;
	animation_set = CAnimationSets::GetInstance()->Get(24);
	SetState(MOVING_WOOD_STATE_MOVING_HORIZONTAL);
}

void CMovingWood::Update(DWORD dt, vector<LPGAMEOBJECT> *listMapObj)
{
	CGameObject::Update(dt, listMapObj);
	if (state == MOVING_WOOD_STATE_MOVING_HORIZONTAL)
	{
		if (x - ((CGame::GetInstance()->GetCamPosX() + CGame::GetInstance()->GetScreenWidth())) < 50)
		{
			vx = -0.03f;
		}
	}
	
	if (state == MOVING_WOOD_STATE_FALLING)
	{
		vy += MARIO_GRAVITY * dt;
	}
	x += dx;
	y += dy;
}

void CMovingWood::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_WOOD_STATE_MOVING_HORIZONTAL:
		vy = 0;
		break;
	case MOVING_WOOD_STATE_FALLING:
		vx = 0;
		break;
	}
}

void CMovingWood::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CMovingWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * amountX;
	b = y + BRICK_BBOX_HEIGHT * amountY;
}
