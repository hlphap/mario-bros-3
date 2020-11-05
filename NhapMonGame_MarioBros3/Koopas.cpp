#include "Koopas.h"
#include "ColorBox.h"
#include "Utils.h"

CKoopas::CKoopas(CMario *m)
{
	mario = m;
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
	//Bi cam thi khong co gia toc trong truong
	//Bị cầm -> hết cầm
	if (isHeld)
	{
		if (!mario->isHoldingShell)
		{
			isHeld = false;
			isKicked = true;
			this->nx = mario->nx;
			mario->Kick();
			SetState(KOOPAS_STATE_MOVING);
		}
			if (mario->nx < 0)
			{
				SetPosition(mario->x - KOOPAS_BBOX_WIDTH + 5, mario->y);
			}
			else
			{
				SetPosition(mario->x + MARIO_BIG_BBOX_WIDTH, mario->y);
			}
			return;
		
	}
	CGameObject::Update(dt);
	vy += ENEMY_GRAVITY;

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

		if (!isHeld)
		{
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.1f;


			if (nx != 0)
			{
				this->nx = -this->nx;
			}
			if (ny != 0)
			{
				vy = 0;
			}
		}
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// Brick defaul
			if (dynamic_cast<CBoundaryBrick*>(e->obj))
			{
				if (e->nx != 0)
				{

					if (isSleeping)
					{
						this->nx = -this->nx;
						x += dx;
					}
				}
			}
			else
				if (dynamic_cast<CColorBox*>(e->obj))
				{

					if (e->nx != 0)
					{
						this->nx = -this->nx;
						x += dx;
					}
					else if (e->ny < 0)
					{
						vy = 0;
					}
				}

		}
		if (isMove) SetState(KOOPAS_STATE_MOVING);
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
		

		
}

			

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (!isMove)
	{
		if (isSleeping)
			ani = KOOPAS_ANI_SHELL_IDLE;
	}
	else if (nx == 1)
	{
		if (!isSleeping)
		{
			ani = KOOPAS_ANI_WALKING_RIGHT;
		}
		else
			if (isSleeping)
			{
				ani = KOOPAS_ANI_SHELL_MOVE;
			}
	}
	else if (nx == -1)
	{
		if (!isSleeping)
		{
			ani = KOOPAS_ANI_WALKING_LEFT;
		}
		else
			if (isSleeping)
			{
				ani = KOOPAS_ANI_SHELL_MOVE;
			}
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}



void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_MOVING:
		isMove = true;
		if (nx == 1)
		{
			if (isKicked)
				vx = KOOPAS_RUNNING_WHEN_KICKED;
			else
				vx = KOOPAS_WALKING_SPEED;
		}
		else
			if (nx == -1)
			{
				if (isKicked)
					vx = -KOOPAS_RUNNING_WHEN_KICKED;
				else
					vx = -KOOPAS_WALKING_SPEED;
			}
		break;
	case KOOPAS_STATE_SLEEP:
		isKicked = false;
		isSleeping = true;
		isMove = false;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE:
		isKicked = false;
		isSleeping = false;
		isMove = false;
		vx = 0;
		vy = 0;
		break;
	}

}