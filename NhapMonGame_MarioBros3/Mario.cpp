#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "PlayScence.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	mario_general = CMarioGeneral::GetInstance();
	mario_general->LoadListAni();

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
	/*for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(dt, coObjects);
	}*/
	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	//Update isSpeedUping 
	if (abs(vx) > MARIO_WALKING_MAX_SPEED&& abs(vx) < MARIO_RUNNING_MAX_SPEED) isSpeedUping = true;
	else
		isSpeedUping = false;

	//Update IsSpeedMax and Update timeStartFly
	if (abs(vx) == MARIO_RUNNING_MAX_SPEED)
	{
		isSpeedMax = true;
		timeStartFly = GetTickCount();
	}
	else
	{
		isSpeedMax = false;
		DebugOut(L"\nTimeStartFly: %d", timeStartFly);
		DebugOut(L"\n now: %d", GetTickCount());
		DebugOut(L"\n Time out: %d", GetTickCount() - timeStartFly);
		if (GetTickCount() - timeStartFly <= 500)
		{
			isKeepJump_HightFlying = true;
		}
	}
	DebugOut(L"\n Van to vx: %f ", vx);
		

	//Update IsFalling
	if (vy > 0)
	{
		isFalling = true;
	} 

	//Update IsAttack BigTail
	if (level == MARIO_LEVEL_BIG_TAIL)
	{
		if (nx == 1)
		{
			if (isAttacking && animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_RIGHT)->IsRenderOver())
			{
				isAttacking = false;
			}
		}
		else if (nx == -1)
		{
			if (isAttacking && animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_LEFT)->IsRenderOver())
				isAttacking = false;
		}
	} 

	//Update IsAttack BigFire
	if (level == MARIO_LEVEL_BIG_FIRE)	{
		if (isOnAir)
		{
			if (nx == 1)
			{
				if (isAttacking && animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_RIGHT)->IsRenderOver())
				{
					isAttacking = false;
				}
			}
			else if (nx == -1)
			{
				if (isAttacking && animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_LEFT)->IsRenderOver())
					isAttacking = false;
			}
		}
		else
		{
			if (nx == 1)
			{
				if (isAttacking && animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_RIGHT)->IsRenderOver())
				{
					isAttacking = false;
				}
			}
			else if (nx == -1)
			{
				if (isAttacking && animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_LEFT)->IsRenderOver())
					isAttacking = false;
			}
		}
		
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
		y += min_ty * dy + ny * 0.1f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

		//DebugOut(L"vy: %f", vy);

	//	if (!isOnAir) isFalling = true;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// Brick defaul
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					isBlockKeepJump = true;
					//isFly = false;
				}
				else
					if (e->ny > 0)
					{
						vy = 0;
						isKeepJump_HightFlying = false;
					}
					else
						if (e->nx != 0)
						{
							vx = 0;
						}
			}
			//Brick Cloud
			else if (dynamic_cast<CCloudBrick*>(e->obj))
			{

				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					//isFly = false;
				}
				else if (e->ny > 0)
				{
					y += dy;
				}
				else
					if (e->nx != 0)
					{
						x += dx;
					}
			}

			//Brick Weak
			else if (dynamic_cast<CWeakBrick*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					//isFly = false;
				}
				else
					if (e->ny > 0)
					{
						vy = 0;
						isKeepJump_HightFlying = false;
					}
					else
						if (e->nx != 0)
						{
							vx = 0;
						}
			}

			//Question Brick
			else if (dynamic_cast<CQuestionBrick*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					//isFly = false;
				}
				else
					if (e->ny > 0)
					{
						vy = 0;
						isKeepJump_HightFlying = false;
					}
					else
						if (e->nx != 0)
						{
							vx = 0;
						}
			}

			//Ground
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					isBlockKeepJump = true;
					//isFly = false;
				}
				else
				if (e->nx != 0)
				{
					vx = 0;
				}
			}

			//ColorBox
			else if (dynamic_cast<CColorBox*>(e->obj))

			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					//isFly = false;
				}
				else if (e->ny > 0)
				{
					y += dy;
				}
				if (e->nx != 0)
				{
					x += dx;
				}
			}

			//Pipe
			else if (dynamic_cast<CPipe*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					isOnAir = false;
					isKeepJump_SlowFalling = false;
					isBlockFall = false;
					isKeepJump_HightFlying = false;
					//isFly = false;
				}
				if (e->nx != 0)
				{
					vx = 0;
				}
			}

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
				/*if (e->nx != 0) x += vx * dt;*/
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
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		switch (level)
		{
		case MARIO_LEVEL_BIG:
			mario_general->SetLevel(MARIO_LEVEL_BIG);

			break;
		case MARIO_LEVEL_SMALL:
			mario_general->SetLevel(MARIO_LEVEL_SMALL);

			break;
		case MARIO_LEVEL_BIG_TAIL:
			mario_general->SetLevel(MARIO_LEVEL_BIG_TAIL);

			break;
		case MARIO_LEVEL_BIG_FIRE:
			mario_general->SetLevel(MARIO_LEVEL_BIG_FIRE);

			break;
		}
	ani = RenderFromAniGroup();


	int alpha = 255;
	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}



int CMario::RenderFromAniGroup()
{
	int aniIndex = -1;
	int ani = -1;
	//DebugOut(L"vx %d", nx);
	//Mario Stop'


	if (vx == 0)
	{
		//Sit
		if (isSitting)
		{
			if (nx < 0) aniIndex = MARIO_ANI_SITTING_LEFT;
			else
				aniIndex = MARIO_ANI_SITTING_RIGHT;
		}
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{
			if (nx < 0)
			{
				aniIndex = MARIO_ANI_FLYING_LEFT;
			}
			else
				aniIndex = MARIO_ANI_FLYING_RIGHT;
		}
		else if (isFalling && isOnAir)
		{

			if (nx < 0)
			{
				aniIndex = MARIO_ANI_FALLING_LEFT;
			}
			else
			{
				aniIndex = MARIO_ANI_FALLING_RIGHT;
			}
		}
		//Idle
		else
		{
			if (nx < 0) aniIndex = MARIO_ANI_IDLE_LEFT;
			else
				aniIndex = MARIO_ANI_IDLE_RIGHT;
		}
	}
	else if (nx == 1)
	{
		// Sit
		if (isSitting)
		{
			aniIndex = MARIO_ANI_SITTING_RIGHT;
		}
		else if ((isSpeedMax) && (isOnAir))
		{
			aniIndex = MARIO_ANI_RUNNING_FLY_RIGHT;
		}
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{
			aniIndex = MARIO_ANI_FLYING_RIGHT;
		}
		else if (isFalling && isOnAir)
		{
			aniIndex = MARIO_ANI_FALLING_RIGHT;
		}
		// Running
		else if ((!isSitting) && (!isOnAir) && (isSpeedMax))
		{
			aniIndex = MARIO_ANI_RUNNING_RIGHT;

		}
		else if ((!isSitting) && (!isOnAir) && (isStop) && (vx < 0))
		{
			aniIndex = MARIO_ANI_WALKING_STOP_LEFT;
		}
		// Go Right
		else
			aniIndex = MARIO_ANI_WALKING_RIGHT;
	}
	else if (nx == -1)
	{
		//Go Left
		if (isSitting)
		{
			aniIndex = MARIO_ANI_SITTING_LEFT;
		}
		else if ((isSpeedMax) && (isOnAir))
		{
			aniIndex = MARIO_ANI_RUNNING_FLY_LEFT;
		}
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{

			aniIndex = MARIO_ANI_FLYING_LEFT;
		}
		else if (isFalling && isOnAir)
		{
			aniIndex = MARIO_ANI_FALLING_LEFT;
		}
		else if ((!isSitting) && (!isOnAir) && (isSpeedMax))
		{
			aniIndex = MARIO_ANI_RUNNING_LEFT;
		}

		else if ((!isSitting) && (!isOnAir) && (isStop) && (vx > 0))
		{
			aniIndex = MARIO_ANI_WALKING_STOP_RIGHT;
		}
		else
			aniIndex = MARIO_ANI_WALKING_LEFT;

	}

	// special MARIO_BIG_TAIL
	if (level == MARIO_LEVEL_BIG_TAIL)
	{
		if (isKeepJump_HightFlying && isOnAir) // Bay Khi Spam S
		{

			if (nx < 0)
			{
				aniIndex = MARIO_ANI_RUNNING_FLY_SLOW_LEFT;
			}
			else
				aniIndex = MARIO_ANI_RUNNING_FLY_SLOW_RIGHT;
		}
		else
			if (isKeepJump_SlowFalling)	// Roi khi Spam S
			{
				if (nx < 0)
				{
					aniIndex = MARIO_ANI_FALLING_SLOW_LEFT;
				}
				else
					aniIndex = MARIO_ANI_FALLING_SLOW_RIGHT;
			}
			else
				if (isSpeedMax && isOnAir && isFalling) // Roi khi chay nhanh
				{
					if (nx < 0)
					{
						aniIndex = MARIO_ANI_RUNNING_FALLING_LEFT;
					}
					else
					{
						aniIndex = MARIO_ANI_RUNNING_FALLING_RIGHT;
					}
				}
		if (isAttacking)
		{
			if (nx < 0)
			{
				aniIndex = MARIO_ANI_ATTACKING_LEFT;
			}
			else
				aniIndex = MARIO_ANI_ATTACKING_RIGHT;
		}

	}

	if (level == MARIO_LEVEL_BIG_FIRE)
	{
		if (isAttacking)
		{
			if (isOnAir)
			{
				if (nx > 0)
					aniIndex = MARIO_ANI_ATTACK_FLY_RIGHT;
				else
					aniIndex = MARIO_ANI_ATTACK_FLY_LEFT;
			}
			else
			{
				if (nx > 0)
					aniIndex = MARIO_ANI_ATTACKING_RIGHT;
				else
					aniIndex = MARIO_ANI_ATTACKING_LEFT;
			}
			
		}
	}


	//	DebugOut(L"AniIndex: %d", aniIndex);
	ani = mario_general->GetAni_Mario(aniIndex);

	////Set toc do hien frame

	//if (isSpeedUping && aniIndex != MARIO_ANI_ATTACKING_LEFT && aniIndex != MARIO_ANI_ATTACKING_RIGHT)
	//{
	//	animation_set->at(ani)->SetHightSpeed(MARIO_RATIO_SPEED_WHEN_SPEEDUP);
	//}
	//if (isSpeedMax && aniIndex != MARIO_ANI_RUNNING_FLY_SLOW_LEFT && aniIndex != MARIO_ANI_RUNNING_FLY_SLOW_RIGHT)
	//{
	//	animation_set->at(ani)->SetHightSpeed(MARIO_RATIO_SPEED_WHEN_SPEEDMAX);
	//}
	return ani;
}

void CMario::DecreaseSpeed(float speedDown)
{
	float DECELERATION;
	if (isSpeedUping)
		DECELERATION = MARIO_RUNNING_DECELERATION;
	else
		DECELERATION = MARIO_WALKING_DECELERATION;
	//DebugOut(L"\nIsSpeedUPing: %d", isSpeedUping);
	//DebugOut(L"\nAcc: %f", DECELERATION);
	if (vx > speedDown)
	{
		vx -= DECELERATION * dt;
		if (vx <= speedDown)
			vx = speedDown;
	}
	else if (vx < speedDown)
	{
		vx += DECELERATION * dt;
		if (vx >= speedDown)
			vx = speedDown;
	}
	last_vx = vx;
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING:
	{
		if (nx == 1)
		{
			// Neu toc do cao hon di bo -> giam toc do 
			if (vx > MARIO_WALKING_MAX_SPEED)
			{
				DecreaseSpeed(MARIO_WALKING_MAX_SPEED);
				//	DebugOut(L"\nMario Speed Down: vx: %f", vx);
			}
			else
			{
				vx += MARIO_WALKING_ACCELERATION * dt;
				if (vx >= MARIO_WALKING_MAX_SPEED)
					vx = MARIO_WALKING_MAX_SPEED;
			}
			break;
		}
		else if (nx == -1)
		{
			// Neu toc do cao hon di bo -> giam toc do 
			if (vx < -MARIO_WALKING_MAX_SPEED)
			{
				DecreaseSpeed(-MARIO_WALKING_MAX_SPEED);
				//	DebugOut(L"\nMario Speed Down: vx: %f", vx);
			}
			else
			{
				vx -= MARIO_WALKING_ACCELERATION * dt;
				if (vx <= -MARIO_WALKING_MAX_SPEED)
					vx = -MARIO_WALKING_MAX_SPEED;
			}
			
			//DebugOut(L"\nMario Speed Up: vx: %f", vx);
			break;
		}
	}

	case MARIO_STATE_SITTING:
	{
		DecreaseSpeed(0);
		//DebugOut(L"\nToc do giam khi Ngoi vx: %f", vx); OKER
		break;
	}
	case MARIO_STATE_RUNNING:
	{
		float ACCELERATION;
		if (!isSpeedUping)
			ACCELERATION = MARIO_WALKING_ACCELERATION;
		else
			ACCELERATION = MARIO_RUNNING_ACCELERATION;
		/*if (isOnAir)
		{
			DecreaseSpeed(MARIO_WALKING_ACCELERATION);
		}*/
		//DebugOut(L"\nMario Speed Up: vx: %f", vx);
		if (nx == 1)
		{
			vx += ACCELERATION * dt;
			if (vx >= MARIO_RUNNING_MAX_SPEED)
			{
				vx = MARIO_RUNNING_MAX_SPEED;
			}
			break;
		}
		else if (nx == -1)
		{
			vx -= ACCELERATION * dt;
			if (vx <= -MARIO_RUNNING_MAX_SPEED)
			{
				vx = -MARIO_RUNNING_MAX_SPEED;
			}
		//	DebugOut(L"\nvx nx = -1: %f", ACCELERATION);
			break;
		}
	}
	case MARIO_STATE_DECREASE_WHEN_RUNNING:
	{
		DecreaseSpeed(0);
		break;
	}

	case MARIO_STATE_JUMPING:
	{
		vy = -MARIO_JUMP_SPEED_Y;
		break;
	}

	case MARIO_STATE_FALLING:	// Roi nhanh
	{
		if (!isBlockFall && isOnAir)
		{
			vy += MARIO_GRAVITY * dt * MARIO_BOUNCE;
		}
		break;
	}


	//=============================SPECIAL STATE MARIO_TAIL=============================
	case MARIO_STATE_BIG_TAIL_KEEP_JUMP_FALL_SLOW: // Roi cham 
	{
		if (isKeepJump_HightFlying)
		{
			SetState(MARIO_STATE_BIG_TAIL_KEEP_JUMP_FLY_HIGHT);
			break;
		}
		vy = -MARIO_GRAVITY * dt;				// Roi cham
		break;
	}
	case MARIO_STATE_BIG_TAIL_KEEP_JUMP_FLY_HIGHT:
	{
		vy = -MARIO_GRAVITY * dt * MARIO_BOUNCE;
		if (nx == 1 && animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_RIGHT)->IsRenderOver())
		{
			animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_RIGHT)->SetCurrentFrame();
			animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_RIGHT)->StartAni();
		}
		else if (nx == -1 && animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_LEFT)->IsRenderOver())
		{
			animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_LEFT)->SetCurrentFrame();
			animation_set->at(MARIO_ANI_BIG_TAIL_FLYING_SLOW_LEFT)->StartAni();
		}
		//isFalling_HightFlying = true;
		break;
	}

	case MARIO_STATE_BIG_TAIL_ATTACK:
	{
		if (nx == 1 && animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_RIGHT)->IsRenderOver())
		{
			animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_RIGHT)->SetCurrentFrame();
			animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_RIGHT)->StartAni();
		}
		else if (nx == -1 && animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_LEFT)->IsRenderOver())
		{
			animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_LEFT)->SetCurrentFrame();
			animation_set->at(MARIO_ANI_BIG_TAIL_ATTACKING_LEFT)->StartAni();
		}
		break;
	}
	
	//=============================END SPECIAL STATE MARIO_TAIL=============================
	
	//=============================SPECIAL STATE MARIO_FIRE=============================
	case MARIO_STATE_BIG_FIRE_ATTACK:
	{
		if (isOnAir)
		{
			if (nx == 1 && animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_RIGHT)->IsRenderOver())
			{
				animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_RIGHT)->SetCurrentFrame();
				animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_RIGHT)->StartAni();
			}
			else if (nx == -1 && animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_LEFT)->IsRenderOver())
			{
				animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_LEFT)->SetCurrentFrame();
				animation_set->at(MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_LEFT)->StartAni();
			}

		}
		else
		{
			if (nx == 1 && animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_RIGHT)->IsRenderOver())
			{
				animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_RIGHT)->SetCurrentFrame();
				animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_RIGHT)->StartAni();
			}
			else if (nx == -1 && animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_LEFT)->IsRenderOver())
			{
				animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_LEFT)->SetCurrentFrame();
				animation_set->at(MARIO_ANI_BIG_FIRE_ATTACKING_LEFT)->StartAni();
			}
		}
	
		break;
	}
	//=============================END SPECIAL STATE MARIO_FIRE=============================
	case MARIO_STATE_STOP_RUNNING:
	{
		DecreaseSpeed(0);
		break;
	}

	case MARIO_STATE_IDLE:
	{
		DecreaseSpeed(0);
		isStop = false;
		break;
	}
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	top = y;
	mario_general->GetBoundingBoxFromGroupAni(left, top, right, bottom);

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

void CMario::Go()
{
	//DebugOut(L"Trang thai tang toc: %b", isSpeedUp);
	//Run
	
	if (isSpeedUp)
	{
		if (vx * nx >= 0)
			SetState(MARIO_STATE_RUNNING);
		else
			SetState(MARIO_STATE_DECREASE_WHEN_RUNNING);
	}
	else
		if (!isSitting)
		{
			SetState(MARIO_STATE_WALKING);
		}

	//DebugOut(L"\nToc do mario vx: %f", vx);
	last_vx = vx;
}


void CMario::Left()
{
	isSitting = false;
	nx = -1;

}

void CMario::Right()
{
	isSitting = false;
	nx = 1;

}

void CMario::Jump()
{
	isOnAir = true;
	isFalling = false;
	SetState(MARIO_STATE_JUMPING);

}
void CMario::Fall()
{
	//isFalling = true;
	SetState(MARIO_STATE_FALLING);
	isBlockFall = true;
	isBlockKeepJump = false;

}

void CMario::Attack()
{
	isAttacking = true;
	if (level == MARIO_LEVEL_BIG_TAIL)
	{
		isKeepJump_HightFlying = false;
		isKeepJump_SlowFalling = false;
		//Bam danh thi bi roi
		SetState(MARIO_STATE_BIG_TAIL_ATTACK);
	}
	else if (level == MARIO_LEVEL_BIG_FIRE)
	{
		SetState(MARIO_STATE_BIG_FIRE_ATTACK);
	}
}

void CMario::KeepJump()
{
	if (isKeepJump_HightFlying)
	{
		isKeepJump_HightFlying = true;
		SetState(MARIO_STATE_BIG_TAIL_KEEP_JUMP_FLY_HIGHT);
	}
	else
	{
		isKeepJump_SlowFalling = true;
		SetState(MARIO_STATE_BIG_TAIL_KEEP_JUMP_FALL_SLOW);
	}

}

void CMario::Sit()
{
	isSitting = true;
	SetState(MARIO_STATE_SITTING);
}

void CMario::Idle()
{
	isSitting = false;
	SetState(MARIO_STATE_IDLE);
}

void CMario::Stop()
{
	isStop = true;
	SetState(MARIO_STATE_STOP_RUNNING);
}
