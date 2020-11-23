#include "Goomba.h"
#include "Utils.h"
#include "ColorBox.h"
CGoomba::CGoomba(CMario *m)
{
	player = m;
	nx = -1;
	SetState(GOOMBA_STATE_MOVE);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	top = y;
	right = left + GOOMBA_BBOX_WIDTH;
	bottom = top + GOOMBA_BBOX_HEIGHT;
	if (state == GOOMBA_STATE_DIE)
		top = top + GOOMBA_BBOX_HEIGHT;
	
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (!isKillByWeapon)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}

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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.1f;

		if (ny < 0)
		{
			vy = 0;
		}
		else
			if (nx != 0)
			{
				backup_vx = vx;
				vx = -vx;
			}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CColorBox*>(e->obj))
			{
				if (e->nx != 0)
				{
					vx = backup_vx;
					x += dx;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}




void CGoomba::Render()
{
	int ani = GOOMBA_ANI_MOVING;
	if (state == GOOMBA_STATE_DIE) {
		if (isKillByWeapon)
			ani = GOOMBA_ANI_DIE_REVERSE;
		else
			ani = GOOMBA_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_MOVE:
		if (nx == 1)
		{
			vx = GOOMBA_SPEED_MOVE;
		}
		else
		{
			vx = -GOOMBA_SPEED_MOVE;
		}
		break;
	case GOOMBA_STATE_DIE:
		if (isKillByWeapon)
		{
			vy = -GOOMBA_SPEED_BOUNCE;
			if (player->nx == 1)
			{
				vx = GOOMBA_SPEED_WHEN_DIE;
			}
			else if (player->nx == -1)
			{
				vx = -GOOMBA_SPEED_WHEN_DIE;
			}
		}
		else
		{
			vy = 0;
			vx = 0;
		}
		break;
	}
}
