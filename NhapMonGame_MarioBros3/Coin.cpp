#include "Coin.h"
#include "WeakBrick.h"

CCoin::CCoin(float x, float y, int type)
{
	SetPosition(x + 4, y);
	minPosY = y - DISTANCE_FROM_QUESTIONBRICK_TO_MINPOSY;
	this->type = type;
	if (this->type == TYPE::COIN_EFFECT)
	{
		vy = -0.4f;
	}

}

void CCoin::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
	vector<LPCOLLISIONEVENT> coObjEvents;
	vector<LPCOLLISIONEVENT> coObjEventsResult;
	coObjEvents.clear();
	if (type == TYPE::COIN_EFFECT)
	{
		if (!isComplete)
			if (y <= minPosY)
			{
				isComplete = true;
				vy = 0;
			}
		CGameObject::Update(dt,listMapObj);
		if (isComplete)
		{
			//vy += ITEM_GRAVITY * dt;
			vy = 0.2f;
			CalcPotentialCollisions(listMapObj, coObjEvents);
		}
		if (coObjEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coObjEvents, coObjEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.1f;
			if (ny < 0)
			{
				vy = 0;
				isActive = false;
			}
			for (UINT i = 0; i < coObjEvents.size(); i++) delete coObjEvents[i];
		}
	}
	else
		if (type == TYPE::COIN_IDLE_STATIC)
		{
			if (GetTickCount() - timeStartTranForM >= TIME_TRANSFORM_FROM_COIN_TO_WEAKBRICK && timeStartTranForM != TIME_DEFAULT)
			{
				SetState(COIN_IDLE_STATIC_TRANFORM_TO_WEAKBRICK);
			}
		}
}


void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_IDLE_STATIC_TRANFORM_TO_WEAKBRICK:
		break;
	}
}


void CCoin::Render()
{
	//RenderBoundingBox();
	if (type == TYPE::COIN_EFFECT)
		ani = ITEM_ANI_COIN_MOVE_FAST;
	else
		if (type == TYPE::COIN_IDLE_STATIC)
			ani = ITEM_ANI_COIN_IDLE;	
		else
			if (type == TYPE::COIN_IDLE_SPIN)
				ani = ITEM_ANI_COIN_MOVE_SLOW;
	animation_set->at(ani)->Render(x, y);
}
void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}
