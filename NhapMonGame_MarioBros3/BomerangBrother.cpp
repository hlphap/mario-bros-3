#include "BomerangBrother.h"
#include "Utils.h"

CBomerangBrother::CBomerangBrother(float x, float y)
{
	this->type = TYPE::BOOMERANG_BROTHER;
	isActive = true;
	minX = x;
	maxX = x + DISTANCE_GO_AROUND;
	SetPosition(x, y);
	vx = 0.02f;
	SetState(BROTHER_MOVING_ATTACK);
}

void CBomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj)
{
	DebugOut(L"\nBoomerang update ne");
	vy += ENEMY_GRAVITY * dt;
	if (state != BOMERANGBROTHER_STATE_DIE)
	{
		if (x < minX)
		{
			SetState(BROTHER_MOVING_ATTACK);
		}
		if (x > maxX)
		{
			SetState(BROTHER_MOVING_RETURN);
		}


		if (countBoomerang < 2)
		{
			if (state == BROTHER_MOVING_ATTACK)
			{
				if (countBoomerang == 0 && timeStartFight == TIME_DEFAULT)
				{
					isCreateBoomerang = true;
					timeStartFight = GetTickCount();
					countBoomerang = 1;
				}
			}
			else
				if (countBoomerang == 1 && state == BROTHER_MOVING_RETURN)
				{
					isCreateBoomerang = true;
					timeStartFight = GetTickCount();
					countBoomerang = 2;
				}
		}

		if (GetTickCount() - timeStartFight > 3000 && timeStartFight != TIME_DEFAULT && countBoomerang == 2)
		{
			timeStartFight = TIME_DEFAULT;
			countBoomerang = 0;
		}
	}

	CGameObject::Update(dt, listMapObj);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != BOMERANGBROTHER_STATE_DIE)
		CalcPotentialCollisions(listMapObj, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;
		if (ny != 0)
		{
			vy = 0;
		}
		// Collision logic with other listMapObj
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CBomerangBrother::Render()
{
	if (state != BOMERANGBROTHER_STATE_READY_TO_FIGHT)
		ani = 0;
	else
		ani = 1;
	if (state == BOMERANGBROTHER_STATE_DIE)
		ani = 2;
	animation_set->at(ani)->Render(x, y);
}

void CBomerangBrother::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOMERANGBROTHER_BBOX_WIDTH;
	b = y + BOMERANGBROTHER_BBOX_HEIGHT;
}

void CBomerangBrother::CreateBoomerang(vector<LPGAMEOBJECT>* listFireBall)
{
	if (isCreateBoomerang)
	{
		SetState(BOMERANGBROTHER_STATE_READY_TO_FIGHT);
		CBomerang* boomerang = new CBomerang(1, x + 10, y);
		listFireBall->push_back(boomerang);
		timeStartFight = GetTickCount64();
		isCreateBoomerang = false;
		if (countBoomerang == 1)
			SetState(BROTHER_MOVING_ATTACK);
		if (countBoomerang == 2)
			SetState(BROTHER_MOVING_RETURN);
	}
}

void CBomerangBrother::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROTHER_MOVING_ATTACK:
		vx = 0.02f;
		break;
	case BROTHER_MOVING_RETURN:
		vx = -0.02f;
		break;
	case BOMERANGBROTHER_STATE_READY_TO_FIGHT:
		break;
	case BOMERANGBROTHER_STATE_DIE:
		vy = 0.01f;
		break;
	}
}
