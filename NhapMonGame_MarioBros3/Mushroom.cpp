#include "Mushroom.h"

CMushroom::CMushroom(float x, float y, int color)
{
	this->color = color;
	type = TYPE::MUSHROOM;
	SetPosition(x, y);
	minPosY = y - QUESTION_BRICK_BBOX_HEIGHT - 1;
	SetState(MUSHROOM_STATE_GROWN_UP);
}

void CMushroom::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
	CGameObject::Update(dt, listMapObj);
	vector<LPCOLLISIONEVENT> coObjEvents;
	vector<LPCOLLISIONEVENT> coObjEventsResult;
	coObjEvents.clear();

	if (!isComplete)
	{
		if (y < minPosY)
		{
			isComplete = true;
			vy = 0;
			vx = 0.03f;	
		}
	}


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

void CMushroom::Render()
{
	if (color == MUSHROOM_RED)
		ani = ITEM_ANI_MUSHROOM_RED;
	else
		if (color == MUSHROOM_GREEN)
			ani = ITEM_ANI_MUSHROOM_GREEN;
	animation_set->at(ani)->Render(x, y);
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_GROWN_UP:
		vy = -MUSHROOM_SPEED_GROWN_UP;
		break;
	}
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}
