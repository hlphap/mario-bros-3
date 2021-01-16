#include "Goomba.h"
#include "Utils.h"
#include "ColorBox.h"
CGoomba::CGoomba(CMario* m, int type, int level)
{
	this->type = TYPE::GOOMBA;
	this->category = CATEGORY::ENEMY;
	player = m;
	this->level = level;
	this->typeColor = type;
	goombaGeneral = new CGoombaGeneral();
	goombaGeneral->LoadListAni();
	nx = -1;
	SetState(GOOMBA_STATE_MOVE);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 20;
	bottom = top + 24;
	if (state == GOOMBA_STATE_DIE)
	{
		top = top - top;
	}
		
	if (level == GOOMBA_LEVEL_HAVE_WING)
	{
		if (!isFlying)
		{
			top = top + 5;
		}
	}
	else
		top = top + 8;
	left = left + 2;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);
	
	if (GetTickCount() - timeStartDie >= 1000 && timeStartDie != TIME_DEFAULT)
	{
		isActive = false;
		timeStartDie = 0;
	} 


	//Follow Mario
	if (!isAllowJump && level == GOOMBA_LEVEL_HAVE_WING)
	{
		if (x - player->x > 0)
		{
			nx = -1;
		}
		else
			nx = 1;
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (!isKillByWeapon)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	if (GetTickCount() - timeStartMove >= 2000 && level == GOOMBA_LEVEL_HAVE_WING)
	{
		isAllowJump = true;
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
			if (isAllowJump)
				numJump++;
			if (numJump > 3)
			{
				isFlying = false;
				timeStartMove = GetTickCount();
				isAllowJump = false;
				numJump = 0;
			}
		}
		else
			if (ny > 0)
			{
				vy = 0;
				isAllowJump = false;
			}
			if (nx != 0)
			{
				backup_vx = vx;
				vx = -vx;
				
				isAllowJump = false;
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
		if (isMoving && isAllowJump)
		{
			DebugOut(L"imhere");
			SetState(GOOMBA_STATE_MOVE);
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}




void CGoomba::Render()
{
	int aniIndex = -1;
	if (isMoving)
	{
		if (level == GOOMBA_LEVEL_HAVE_WING)
		{
			if (isFlying)
				aniIndex = GOOMBA_ANI_FLYING;
			else
				aniIndex = GOOMBA_ANI_HAVE_WING_MOVING;
		}
		else
			aniIndex = GOOMBA_ANI_MOVING;
	}
	else
	{
		if (isKillByWeapon)
			aniIndex = GOOMBA_ANI_DIE_BY_WEAPON;
		else
			aniIndex = GOOMBA_ANI_DIE;
	}
	ani = goombaGeneral->GetAni_Goomba(typeColor, aniIndex);
	//DebugOut(L"Ani Gomba %d \n", ani);
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_MOVE:
		isMoving = true;
		if (level == GOOMBA_LEVEL_HAVE_WING)
		{
			if (isAllowJump)
			{
				if (numJump <= 2) //Nhayr laanf 2
				{
					vy = -0.06;
					isFlying = true;
				}
				else
				{
					vy = -0.2;
					isFlying = true;
				}
			}
			else
				vy = 0;
			vx = nx * GOOMBA_SPEED_MOVE;
		}
		else
			if (level == GOOMBA_LEVEL_DEFAULT)
			{
				vx = nx * GOOMBA_SPEED_MOVE;
			}
		break;
	case GOOMBA_STATE_DIE:
		isMoving = false;
		if (timeStartDie == TIME_DEFAULT)
			timeStartDie = GetTickCount();
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
