#include "Tail.h"
#include "Utils.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopas.h"

CTail::CTail()
{
	vy = 0;
}

void CTail::Render()
{
	//DebugOut(L"Imhera");
	//RenderBoundingBox();
}

void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TAIL_BBOX_WIDTH;
	b = y + TAIL_BBOX_HEIGHT;
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TAIL_CAN_KILL:
	{
		canKill = true;
		if (nx == 1)
		{
			vx = TAIL_SPEED_FLY;
		}
		else
		{
			vx = -TAIL_SPEED_FLY;
		}
		break;
	}
	case TAIL_CANNOT_KILL:
	{
		canKill = false;
		break;
	}
	}

}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

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
			y += min_ty * dy + ny * 0.4f;
		
			if (nx != 0)
				x += dx;

		//if (nx != 0) vx = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->nx != 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						if (canKill)
						{
							goomba->isKillByWeapon = true;
							goomba->SetState(GOOMBA_STATE_DIE);
							goomba->vy = -GOOMBA_JUMP_DEFLECT_SPEED;
						}
							
					}
				}
			}
			else
				if (dynamic_cast<CKoopas*>(e->obj))
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
					if (e->nx != 0 || e->ny!=0)
					{
						if (canKill)
						{
							if (koopas->GetState() != KOOPAS_STATE_DIE)
							{
								koopas->vy = -GOOMBA_JUMP_DEFLECT_SPEED;
								koopas->SetState(KOOPAS_STATE_SLEEP);
								if (koopas->GetState() == KOOPAS_STATE_SLEEP)
								{
									koopas->vy = -KOOPAS_JUMP_DEFLECT_SPEED;
								}
								koopas->isKillByWeapon = true;
							}
						}
					}
				}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

CTail* CTail::__instance = NULL;
CTail* CTail::GetInstance()
{
	if (__instance == NULL) __instance = new CTail();
	return __instance;
}
