#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE); 

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

  			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	CMarioGeneral* mario_general = new CMarioGeneral();
	//mario_general = CMarioGeneral::GetInstance();
	mario_general->LoadListAni();
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		switch (level)
		{
		case MARIO_LEVEL_BIG:
			mario_general->SetLevel(MARIO_LEVEL_BIG);
			ani = RenderFromAniGroup(mario_general);
			break;
		case MARIO_LEVEL_SMALL:
			mario_general->SetLevel(MARIO_LEVEL_SMALL);
			ani = RenderFromAniGroup(mario_general);
			break;
		}



	int alpha = 255;
	if (untouchable) alpha = 128;
	/*if (speed_Up) {
		animation_set->at(ani)->SetHightSpeed();
	}*/
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}



int CMario::RenderFromAniGroup(CMarioGeneral* anigroup)
{
	int aniIndex = -1;
	int ani = -1;
	DebugOut(L"vx %f", vx);
	//Mario Stop
	if (vx == 0)
	{
		if (nx < 0) aniIndex = MARIO_ANI_IDLE_LEFT;
		else
			aniIndex = MARIO_ANI_IDLE_RIGHT;
		//Mario Sitting
		//if ((state == MARIO_STATE_SITTING) && (!isJump))
		//{
		//	if (nx > 0) aniIndex = MARIO_ANI_BIG_SITTING_RIGHT;
		//	else aniIndex = MARIO_ANI_BIG_SITTING_LEFT;
		//}
		////Mario Jumping
		//else if (isJump)
		//{
		//	if (nx > 0) aniIndex = MARIO_ANI_BIG_FLY_RIGHT;
		//	else
		//		aniIndex = MARIO_ANI_BIG_FLY_LEFT;
		//}
		////Mario Idle
		//else
		//{
		//	if (nx > 0) aniIndex = MARIO_ANI_BIG_IDLE_RIGHT;
		//	else aniIndex = MARIO_ANI_BIG_IDLE_LEFT;
		//}
	}
	// Mario On The Right
	else if (nx == -1)
	{
		aniIndex = MARIO_ANI_WALKING_LEFT;

		//Mario Sitting
		//if ((state == MARIO_STATE_SITTING) && (!isJump))
		//	aniIndex = MARIO_ANI_BIG_SITTING_RIGHT;
		//else if (vx < 0 && (!isJump))		//Mario Moving Left
		//{
		//	if (downDirectKey == 1)	// Mario 
		//	{
		//		aniIndex = MARIO_ANI_BIG_STOP_RIGHT;
		//	}
		//	else
		//		aniIndex = MARIO_ANI_BIG_WALKING_RIGHT;
		//}
		//else
		//{
		//	aniIndex = MARIO_ANI_BIG_WALKING_RIGHT;
		//}
	}
	else if (nx == 1) //(vx < 0) // di chuyen sang trai
	{
		aniIndex = MARIO_ANI_WALKING_RIGHT;
		//if ((state == MARIO_STATE_SITTING) && (!isJump)) // neu  trang thai la ngoi + khong bay
		//	aniIndex = MARIO_ANI_BIG_SITTING_LEFT;	// ani = ngoi
		//else if (vx > 0 && (!isJump)) //neu trang thai dung dot ngot huong phia ben phai va khong bay
		//{
		//	if (downDirectKey == -1)
		//		aniIndex = MARIO_ANI_BIG_STOP_LEFT;
		//	else
		//		aniIndex = MARIO_ANI_BIG_WALKING_LEFT;
		//}
		//else
		//	aniIndex = MARIO_ANI_BIG_WALKING_LEFT;	// di chuyen sang trai binh thuong
	}

	ani = anigroup->GetAni_Mario(aniIndex);
	return ani;
}

void CMario::DecreaseSpeed()
{
	float ACCELERATOR;
		ACCELERATOR = MARIO_STOP_WHEN_WALKING_ACCELERATOR;
	if (vx > 0)
	{
		vx -= ACCELERATOR * dt;
		if (vx < 0)
			vx = 0;
	}
	else
	{
		vx += ACCELERATOR * dt;
		if (vx > 0)
			vx = 0;
	}
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx += MARIO_WALKING_ACCELERATOR * dt;
		if (vx >= MARIO_WALKING_MAX)
			vx = MARIO_WALKING_MAX;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx -= MARIO_WALKING_ACCELERATOR * dt;
		if (vx <= -MARIO_WALKING_MAX)
			vx = -MARIO_WALKING_MAX;
		nx = -1;
		break;
	case MARIO_STATE_IDLE:
		DecreaseSpeed();
		break;

	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

