#include "Coin.h"

CCoin::CCoin(float x, float y, int type)
{
	SetPosition(x + 4, y);
	minPosY = y - DISTANCE_FROM_QUESTIONBRICK_TO_MINPOSY;
	this->typeCoin = type;
	if (this->typeCoin == COIN_TYPE_EFFECT)
	{
		vy = -0.2f;
	}
		
}

void CCoin::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
	vector<LPCOLLISIONEVENT> coObjEvents;
	vector<LPCOLLISIONEVENT> coObjEventsResult;
	coObjEvents.clear();
	if (typeCoin == COIN_TYPE_EFFECT)
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
			vy += ITEM_GRAVITY * dt;
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
			}
			if (nx != 0)
			{
				backup_vx = vx;
				vx = -vx;
			}

			for (UINT i = 0; i < coObjEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coObjEventsResult[i];
				if (dynamic_cast<CColorBox*>(e->obj))
				{
					CColorBox* colorbox = dynamic_cast<CColorBox*>(e->obj);
					if (e->nx != 0)
					{
						vx = backup_vx;
						x += dx;
						DebugOut(L"Dx: %f\n", dx);
					}
				}
			}
			for (UINT i = 0; i < coObjEvents.size(); i++) delete coObjEvents[i];
		}
	}
}


void CCoin::SetState(int state)
{

}


void CCoin::Render()
{
	if (typeCoin == COIN_TYPE_EFFECT)
		ani = ITEM_ANI_COIN_MOVE_FAST;
	else
		if (typeCoin == COIN_TYPE_IDLE_STATIC)
			ani = ITEM_ANI_COIN_IDLE;
		else
			if (typeCoin == COIN_TYPE_IDLE_SPIN)
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
