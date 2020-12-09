#include "Koopas.h"
#include "ColorBox.h"
#include "Utils.h"
#include "QuestionBrick.h"

CKoopas::CKoopas(CMario* m, int type, int level)
{
	nx = -1;
	this->type = type;
	this->level = level;
	koopasGeneral = CKoopasGeneral::GetInstance();
	koopasGeneral->LoadListAni();
	player = m;
	SetState(KOOPAS_STATE_MOVING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
	if (isSleeping)	
		top = top + KOOPAS_BBOX_HEIGHT_SLEEP;
	if (state == KOOPAS_STATE_DIE)
	{
		top = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Hoi sinh
	if (state == KOOPAS_STATE_SLEEP && timeStartSleep != 0 && GetTickCount() - timeStartSleep >= 5000)
	{
		level++;
		isSleeping = false;
		if (isHeld)
		{
			x += rangeX;
			y -= rangeY;
			isHeld = false; // Khi nó hồi sinh thì không bị cầm nưa
		}
		nx = -player->nx;
		SetState(KOOPAS_STATE_MOVING);
	}
	//Bi cam thi khong co gia toc trong truong
	//Bị cầm -> hết cầm
	if (isHeld)
	{
		if (!player->isHoldingShell)
		{
			isHeld = false;
			isKicked = true;
			this->nx = player->nx;
			player->Kick();
			SetState(KOOPAS_STATE_MOVING);
		}
		if (player->level == MARIO_LEVEL_BIG || player->level == MARIO_LEVEL_BIG_FIRE)
		{
			if (player->nx < 0)
				rangeX = -KOOPAS_BBOX_WIDTH + 5;
			else
				rangeX = MARIO_BIG_BBOX_WIDTH - 3;
			rangeY = 2;
		}
		else if (player->level == MARIO_LEVEL_BIG_TAIL)
		{
			if (player->nx < 0)
				rangeX = -KOOPAS_BBOX_WIDTH + 12;
			else
				rangeX = MARIO_BIG_TAIL_BBOX_WIDTH + 5;
			rangeY = 1;
		}
		else if (player->level == MARIO_LEVEL_SMALL)
		{
			if (player->nx < 0)
				rangeX = -KOOPAS_BBOX_WIDTH + 5;
			else
				rangeX = MARIO_SMALL_BBOX_WIDTH - 4;
			rangeY = 12;
		}
		SetPosition(player->x + rangeX, player->y - rangeY);
		return;
	}
	else //Mario khong giu rua
	{
		player->isHoldingShell = false;
	}
	CGameObject::Update(dt);
	vy += ENEMY_GRAVITY * dt;
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
		y += min_ty * dy + ny * 0.1f;
		if (ny != 0)
		{
			vy = 0;
		}
		// Collision logic with other listMapObj
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// Brick defaul
			if (dynamic_cast<CColorBox*>(e->obj))
			{
				CColorBox* colorbox = dynamic_cast<CColorBox*>(e->obj);
				if (e->nx != 0)
				{
					x += dx;
				}
				else if (e->ny < 0)
				{
					if (!isSleeping && level != KOOPAS_LEVEL_HAVE_WING)
					{
						if (x <= colorbox->x)
						{
							x = colorbox->x;
							this->nx = 1;
						}
						else if (x + KOOPAS_BBOX_WIDTH >= colorbox->x + colorbox->amountX * BRICK_BBOX_WIDTH)
						{
							x = colorbox->x + colorbox->amountX * BRICK_BBOX_WIDTH - KOOPAS_BBOX_WIDTH;
							this->nx = -1;
						}
					}
				}
			}
			else
				if (e->nx != 0)
				{
					if (e->nx > 0)
					{
						this->nx = 1;
					}
					else
						this->nx = -1;
				}
		}
		if (isMoving) SetState(KOOPAS_STATE_MOVING);
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}



void CKoopas::Render()
{
	int aniIndex = -1;	
	if (isMoving)
	{
		if (level == KOOPAS_LEVEL_HAVE_WING)
		{
			if (nx > 0)
				aniIndex = KOOPAS_ANI_FLYING_RIGHT;
			else
				aniIndex = KOOPAS_ANI_FLYING_LEFT;
		}
		else
			if (level == KOOPAS_LEVEL_DEFAULT)
			{
				if (nx > 0)
					aniIndex = KOOPAS_ANI_WALKING_RIGHT;
				else
					aniIndex = KOOPAS_ANI_WALKING_LEFT;
			}
			else
			{
				if (!isKillByWeapon)
					aniIndex = KOOPAS_ANI_SHELL_MOVING;
				else
					aniIndex = KOOPAS_ANI_SHELL_OVERTURNED_MOVING;
			}
	}
	else
		if (!isKillByWeapon)
			aniIndex = KOOPAS_ANI_SHELL_IDLE;
		else
			aniIndex = KOOPAS_ANI_SHELL_OVERTURNED_IDLE;
	ani = koopasGeneral->GetAni_Koopas(type, aniIndex);
//	DebugOut(L"Koopas Ani %d", ani);
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}



void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_MOVING:
		isMoving = true;
		if (level == KOOPAS_LEVEL_HAVE_WING)
		{
			vy = -KOOPAS_SPEED_BOUNCE;
			if (nx > 0)
			{
				vx = KOOPAS_WALKING_SPEED;
			}
			else
				vx = -KOOPAS_WALKING_SPEED;
		}
		else
			if (level == KOOPAS_LEVEL_DEFAULT)
			{
				if (nx > 0)
				{
					vx = KOOPAS_WALKING_SPEED;
				}
				else
					vx = -KOOPAS_WALKING_SPEED;
			}
		else
			if (level == KOOPAS_LEVEL_SHELL)
			{
				if (nx > 0)
				{
					vx = KOOPAS_RUNNING_WHEN_KICKED;
				}
				else
					vx = -KOOPAS_RUNNING_WHEN_KICKED;
			}
		break;
	case KOOPAS_STATE_SLEEP:
		timeStartSleep = GetTickCount();
		isKicked = false;
		isSleeping = true;
		isMoving = false;
		level = KOOPAS_LEVEL_SHELL;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE:
		isKicked = false;
		isSleeping = false;
		isMoving = false;
		level = KOOPAS_LEVEL_SHELL;
		vx = 0;
		vy = 0;
		break;
	}

}