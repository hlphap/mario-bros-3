#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "Koopas.h"
#include "PlayScence.h"
#include "Switch_P.h"

CMario::CMario(float x, float y) : CGameObject()
{
	category = CATEGORY::PLAYER;
	type = TYPE::MARIO;
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

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *listMapObj, vector<LPGAMEOBJECT>* listEnemy, vector<LPGAMEOBJECT>* listItem, vector<LPGAMEOBJECT> *listEffect)
{
#pragma region Update Mario
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;



	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	//Update IsFalling
	if (vy > 0)
	{
		isFalling = true;
	}

	//Update isSpeedUping 
	if (abs(vx) > MARIO_WALKING_MAX_SPEED&& abs(vx) < MARIO_RUNNING_MAX_SPEED) isSpeedUping = true;
	else
		isSpeedUping = false;

	//Update IsSpeedMax and Update timeAllowFly
	if (abs(vx) == MARIO_RUNNING_MAX_SPEED)
	{
		isSpeedMax = true;
		if (!isOnAir)
		{
			timeAllowFly = GetTickCount();
		}
	}
	else
	{
		isSpeedMax = false;
	}


	//Update isKicking
	if (GetTickCount() - timeStartKick >= MARIO_TIME_KICK)
	{
		timeStartKick = TIME_DEFAULT;
		isKicking = false;
	}

	if (GetTickCount() - timeAllowFly <= MARIO_TIME_ALLOWED_FLY)
	{
		isKeepJump_HightFlying = true;
	}
	//Update IsAttack BigTail
	if (level == MARIO_LEVEL_BIG_TAIL)
	{
		tail = CTail::GetInstance();
		tail->nx = nx;
		if (isAttacking)
		{
			tail->SetState(TAIL_CAN_KILL);
		}
		else
		{
			if (nx == 1)
				tail->SetPosition(x, y + MARIO_D_HEED_TO_TAIL_ATTACK);
			else
				tail->SetPosition(x + MARIO_BIG_TAIL_BBOX_WIDTH + 8, y + MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->SetState(TAIL_CANNOT_KILL);
		}
		tail->Update(dt, listMapObj, listEnemy,listItem, listEffect); // Duoi thuoc Mario Update Duoi trong Mario
		if (GetTickCount() - timeStartAttack >= MARIO_TIME_BIG_TAIL_ATTACK)
		{
			timeStartAttack = TIME_DEFAULT;
			isAttacking = false;
		}
		//Update thoi gian bay
		if (isKeepJump_HightFlying)
		{
			if (!isKeepJump)
				timeStartFly = GetTickCount();
			else
				if (GetTickCount() - timeStartFly >= MARIO_TIME_FLYING_MAX)
				{
					isKeepJump_HightFlying = false;
					timeStartFly = TIME_DEFAULT;
				}
		}
	}
	//Update IsAttack BigFire
	else if (level == MARIO_LEVEL_BIG_FIRE)
	{
		if (isAttacking)
		{
			bullet = new CBullet();
			bullet->nx = nx;
			bullet->timeStartAttack = GetTickCount();
			if (nx == 1)
			{
				bullet->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y + MARIO_D_HEED_TO_HAND_ATTACK);
				bullet->SetState(BULLET_STATE_FLY_RIGHT);
			}
			else if (nx == -1)
			{
				bullet->SetPosition(x, y + MARIO_D_HEED_TO_HAND_ATTACK);
				bullet->SetState(BULLET_STATE_FLY_LEFT);
			}
		}
		if (!isOnAir)
		{
			if (GetTickCount() - timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_GROUND)
			{
				timeStartAttack = TIME_DEFAULT;
				isAttacking = false;
			}
		}
		else
		{
			if (GetTickCount() - timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_AIR)
			{
				timeStartAttack = TIME_DEFAULT;
				isAttacking = false;
			}
		}
	}
#pragma endregion

#pragma region Colision with listMapObj (MapGame)
	// Colision with listMapObj (Map Game)
	vector<LPCOLLISIONEVENT> coObjEvents;
	vector<LPCOLLISIONEVENT> coObjEventsResult;
	coObjEvents.clear();
	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
	{
		CalcPotentialCollisions(listMapObj, coObjEvents);
	}
	// No collision occured, proceed normally
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

		//Va cham voi listMapObj thì về trạng thái OnGround
		if (ny < 0)
		{
			backup_vy = vy;
			vy = 0;
			isOnAir = false;
			isBlockFall = false;
			isKeepJump_SlowFalling = false;
			isKeepJump_HightFlying = false;
			isKeepJump = false;
			numFall = 0;

			//Va cham voi Ground thi reset Score
			createdScore = false;
			score = 100;
		}
		// Collision logic with listMapObj
		for (UINT i = 0; i < coObjEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coObjEventsResult[i];

			// Brick defaul
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny > 0)
				{
					vy = 0;
					
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
				if (e->ny > 0)
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
				if (e->ny > 0)
				{
					vy = 0;
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
				CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
				if (e->ny > 0)
				{
					vy = 0;
					if (questionBrick->isItem)
					{
						//Update typeQuestion
						if (questionBrick->typeQuestion == QUESTION_TYPE_COIN)
						{
							questionBrick->typeItem = ITEM_LEVEL_COIN;
						}
						else
						{
							if (level == MARIO_LEVEL_SMALL)
								questionBrick->typeItem = ITEM_LEVEL_MUSHROOM;
							else
								if (level == MARIO_LEVEL_BIG)
								{
									questionBrick->typeItem = ITEM_LEVEL_TREE_LEAF;
								}
								else
										questionBrick->typeItem = ITEM_LEVEL_TREE_LEAF;
						}
						questionBrick->SetState(QUESTION_STATE_MOVE_UP);
					}					
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
				if (e->nx != 0)
				{
					vx = 0;
				}
			}

			//ColorBox
			else if (dynamic_cast<CColorBox*>(e->obj))
			{
				if (e->ny > 0)
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
				if (e->nx != 0)
				{
					vx = 0;
				}
			}
				else if (dynamic_cast<CPortal*>(e->obj))
				{
					/*if (e->nx != 0) x += vx * dt;*/
					CPortal* p = dynamic_cast<CPortal*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coObjEvents.size(); i++) delete coObjEvents[i];
#pragma endregion

#pragma region Colision with listEnemy
	vector<LPCOLLISIONEVENT> coEnemyEvents;
	vector<LPCOLLISIONEVENT> coEnemyEventsResult;

	coEnemyEvents.clear();
	// turn off collision when die 
	if (state != MARIO_STATE_DIE && untouchable==0)
	{
		CalcPotentialCollisions(listEnemy, coEnemyEvents);
	}

	if (coEnemyEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
                       
		FilterCollision(coEnemyEvents, coEnemyEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;


		//Va cham voi listEnemy khi đang bay thì không về trạng thái OnGround
		if (ny < 0)
		{
			backup_vy = vy;
			vy = 0;
			y += min_ty * dy + ny * 0.1f;
			if (createdScore)
				score *= 2;
			createdScore = true;
			CScoreEffect *scoreEffect = new CScoreEffect(x, y);
			scoreEffect->SetScore(score);
			listEffect->push_back(scoreEffect);
		/*	isOnAir = false;
			isBlockFall = false;
			isKeepJump_SlowFalling = false;
			isKeepJump_HightFlying = false;
			isKeepJump = false;
			numFall = 0;*/
		}
		else
			if (ny > 0)
			{
				y -= min_ty * dy + ny * 0.1f;
				if (untouchable == 0)
				{
						if (level > MARIO_LEVEL_SMALL)
						{
							level--;
							StartUntouchable();
						}
						else
						{
							Jump();
							Fall();
							SetState(MARIO_STATE_DIE);
						}

				}
			}
		for (UINT i = 0; i < coEnemyEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEnemyEventsResult[i];
			//Va chạm với quái
			if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_SLEEP)
					{
						//DebugOut(L"Sleep");
						if (koopas->level > 1)
						{
							koopas->level--;
						}
						else
							koopas->SetState(KOOPAS_STATE_SLEEP);
						Jump();
						Fall();
					}
					else
					{
						koopas->isKicked = true;
						if (x < koopas->x)
						{
							Right();
							koopas->nx = 1;
						}
						else
						{
							Left();
							koopas->nx = -1;
						}
						vy = backup_vy;
						y += dy;
						koopas->SetState(KOOPAS_STATE_MOVING);
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (koopas->GetState() != KOOPAS_STATE_SLEEP)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level--;
								StartUntouchable();
							}
							else
							{
								Jump();
								Fall();
								SetState(MARIO_STATE_DIE);
							}
						}
						else
						{
							//Khong tang toc (ko giu A) thi da ruaf
							if (!isHoldShell)
							{
								isHoldingShell = false;
								koopas->isHeld = false;
								Kick();
								if (nx < 0) koopas->nx = 1;
								else
									koopas->nx = -1;
								koopas->isKicked = true;
								koopas->SetState(KOOPAS_STATE_MOVING);
							}
							//Giu rua
							else
							{
								isHoldingShell = true;
								koopas->isHeld = true;
							}
						}
					}
				}
			} // if Goomba
			else
				if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							
							if (goomba->level == GOOMBA_LEVEL_HAVE_WING)
								goomba->level = GOOMBA_LEVEL_DEFAULT;
							else
								if (goomba->level == GOOMBA_LEVEL_DEFAULT)
									goomba->SetState(GOOMBA_STATE_DIE);
							goomba->isKillByWeapon = false;
							Jump();
							Fall();
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
									level--;
									StartUntouchable();
								}
								else
								{
									Jump();
									Fall();
									vx = 0;
									SetState(MARIO_STATE_DIE);
								}

							}
						}
					}
				}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEnemyEvents.size(); i++) delete coEnemyEvents[i];
#pragma endregion

#pragma region Colision with listItem
//P_Switch
	vector<LPCOLLISIONEVENT> coItemEvents;
	vector<LPCOLLISIONEVENT> coItemEventsResult;
	coItemEvents.clear();
	// turn off collision when die 
	CalcPotentialCollisions(listItem, coItemEvents);
	if (coItemEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coItemEvents, coItemEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// Collision logic with listMapObj
		for (UINT i = 0; i < coItemEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coItemEventsResult[i];
			if (e->obj->type == TYPE::SWITCH_P)
			{
				CSwitch_P* switchP = dynamic_cast<CSwitch_P*>(e->obj);
				if (e->ny < 0)
				{
					switchP->SetState(SWITCH_P_STATE_PRESSED);
					switchP->TranFormationBrick(listMapObj, listItem);
					Jump();
					Fall();
				}
			}
		}
	}
//Item khac
	for (int i = 0; i < listItem->size(); i++)
	{
		if (listItem->at(i) != NULL)
		{
			if (isCollisionWithObj(listItem->at(i)))
			{
				if (listItem->at(i)->type == TYPE::MUSHROOM)
				{
					level = MARIO_LEVEL_BIG;
					listItem->at(i)->isActive = false;
				}
				else
				if (listItem->at(i)->type == TYPE::LEAF_TREE)
				{
					level = MARIO_LEVEL_BIG_TAIL;
					listItem->at(i)->isActive = false;
				}
				else
					if (listItem->at(i)->type == TYPE::COIN_IDLE_STATIC || listItem->at(i)->type == TYPE::COIN_IDLE_SPIN)
					{
						listItem->at(i)->isActive = false;
					}
			}
		}
	}



#pragma endregion



}

void CMario::Render()
{
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		ani = RenderFromAniGroup();
	int alpha = 255;
	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(x,y,alpha);
	RenderBoundingBox();
}



int CMario::RenderFromAniGroup()
{
	int aniIndex = -1;
	int ani = -1;
	if (!isWalking)
	{
		//Ngồi
		if (isSitting)
		{
			if (nx < 0) aniIndex = MARIO_ANI_SITTING_LEFT;
			else
				aniIndex = MARIO_ANI_SITTING_RIGHT;
		}
		//Cầm rùa
		else if (isHoldingShell)
		{
			if (isOnAir)
			{
				if (nx < 0)
					aniIndex = MARIO_ANI_HOLD_FLYING_LEFT;
				else
					aniIndex = MARIO_ANI_HOLD_FLYING_RIGHT;
			}
			else
			{
				if (nx < 0) aniIndex = MARIO_ANI_HOLD_IDLE_LEFT;
				else
					aniIndex = MARIO_ANI_HOLD_IDLE_RIGHT;
			}
		}
		//Đá rùa
		else if (isKicking)
		{
			if (nx < 0)
				aniIndex = MARIO_ANI_KICK_LEFT;
			else
			{
				aniIndex = MARIO_ANI_KICK_RIGHT;
			}
		}
		//Bay
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{
			if (nx < 0)
			{
				aniIndex = MARIO_ANI_FLYING_LEFT;
			}
			else
				aniIndex = MARIO_ANI_FLYING_RIGHT;
		}
		//Rơi
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
		//Đứng yên
		else
		{
			if (nx < 0) aniIndex = MARIO_ANI_IDLE_LEFT;
			else
				aniIndex = MARIO_ANI_IDLE_RIGHT;
		}
	}
	else if (nx == 1)
	{
		//Ngồi
		if (isSitting)
		{
			aniIndex = MARIO_ANI_SITTING_RIGHT;
		}
		//Cầm rùa
		else if (isHoldingShell)
		{
			if (isOnAir)
			{
				aniIndex = MARIO_ANI_HOLD_FLYING_RIGHT;
			}
			else
			{
				aniIndex = MARIO_ANI_HOLD_WALKING_RIGHT;
			}
		}
		//Đá rùa
		else if (isKicking)
		{
			aniIndex = MARIO_ANI_KICK_RIGHT;
		}
		//Bay khi đạt vận tốc tối đa
		else if ((isKeepJump_HightFlying) && (isOnAir))
		{
			aniIndex = MARIO_ANI_FLY_WHEN_RUNNING_RIGHT;
		}
		//Bay (nhảy)
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{
			aniIndex = MARIO_ANI_FLYING_RIGHT;
		}
		//Rơi
		else if (isFalling && isOnAir)
		{
			aniIndex = MARIO_ANI_FALLING_RIGHT;
		}
		//Chạy dang tay
		else if ((!isSitting) && (!isOnAir) && (isSpeedMax))
		{
			aniIndex = MARIO_ANI_RUNNING_RIGHT;

		}
		//Trượt
		else if ((!isSitting) && (!isOnAir) && (isStop) && (vx < 0))
		{
			aniIndex = MARIO_ANI_STOP_RIGHT;
		}
		//Đi phải
		else
		{
			aniIndex = MARIO_ANI_WALKING_RIGHT;
		}
			
	}
	else if (nx == -1)
	{
		//Ngồi
		if (isSitting)
		{
			aniIndex = MARIO_ANI_SITTING_LEFT;
		}
		//Cầm rùa
		else if (isHoldingShell)
		{
			if (isOnAir)
			{
				aniIndex = MARIO_ANI_HOLD_FLYING_LEFT;
			}
			else
			{
				aniIndex = MARIO_ANI_HOLD_WALKING_LEFT;
			}
		}
		//Đá rùa
		else if (isKicking)
		{
			aniIndex = MARIO_ANI_KICK_LEFT;
		}
		//Bay khi đạt tốc độ cao
		else if ((isSpeedMax) && (isOnAir))
		{
			aniIndex = MARIO_ANI_FLY_WHEN_RUNNING_LEFT;
		}
		//Bay (nhảy)
		else if ((!isSitting) && (isOnAir) && (!isFalling))
		{
			aniIndex = MARIO_ANI_FLYING_LEFT;
		}
		//Rơi
		else if (isFalling && isOnAir)
		{
			aniIndex = MARIO_ANI_FALLING_LEFT;
		}
		//Chạy dang tay
		else if ((!isSitting) && (!isOnAir) && (isSpeedMax))
		{
			aniIndex = MARIO_ANI_RUNNING_LEFT;
		}
		//Trượt
		else if ((!isSitting) && (!isOnAir) && (isStop) && (vx > 0))
		{
			aniIndex = MARIO_ANI_STOP_LEFT;
		}
		//Đi trái
		else
			aniIndex = MARIO_ANI_WALKING_LEFT;

	}

	//============================================================END GENERAL=================================
	ani = mario_general->GetAni_Mario(level,aniIndex);

	// special MARIO_BIG_TAIL
	if (level == MARIO_LEVEL_BIG_TAIL && !isSitting && !isHoldingShell)
	{
		if (isKeepJump && isOnAir)
		{
			if (isKeepJump_HightFlying) // Bay Khi Spam S
			{
				if (nx < 0)
				{
					ani = MARIO_ANI_BIG_TAIL_KEEPJUMP_FLYING_LEFT;
				}
				else
					ani = MARIO_ANI_BIG_TAIL_KEEPJUMP_FLYING_RIGHT;
			}
			else if (isKeepJump_SlowFalling)	// Roi khi Spam S
			{
				if (nx < 0)
				{
					ani = MARIO_ANI_BIG_TAIL_KEEPJUMP_FALLING_LEFT;
				}
				else
					ani = MARIO_ANI_BIG_TAIL_KEEPJUMP_FALLING_RIGHT;
			}
		}
		else if (isKeepJump_HightFlying && isOnAir && isFalling) // Roi khi chay nhanh
		{
			if (nx < 0)
			{
				ani = MARIO_ANI_BIG_TAIL_FALLING_WHEN_RUNNING_LEFT;
			}
			else
			{
				ani = MARIO_ANI_BIG_TAIL_FALLING_WHEN_RUNNING_RIGHT;
			}
		}
		if (isAttacking)
		{
			if (nx < 0)
			{
				if (this->ani != MARIO_ANI_BIG_TAIL_ATTACK_LEFT)
				{
					ani = MARIO_ANI_BIG_TAIL_ATTACK_LEFT;
					animation_set->at(ani)->SetCurrentFrame();
				}
					ani = MARIO_ANI_BIG_TAIL_ATTACK_LEFT;
			}
			else
			{
				if (this->ani != MARIO_ANI_BIG_TAIL_ATTACK_RIGHT)
				{
					//DebugOut(L"Setani\n");
					ani = MARIO_ANI_BIG_TAIL_ATTACK_RIGHT;
					animation_set->at(ani)->SetCurrentFrame();
				}
					ani = MARIO_ANI_BIG_TAIL_ATTACK_RIGHT;
			}
				
		}

	}

	if (level == MARIO_LEVEL_BIG_FIRE && !isSitting)
	{
		if (isAttacking)
		{
			if (isOnAir)
			{
				if (nx < 0)
				{
					if (this->ani != MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_LEFT)
					{
						ani = MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_LEFT;
						animation_set->at(ani)->SetCurrentFrame();
					}
					ani = MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_LEFT;
				}
				else
				{
					if (this->ani != MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_RIGHT)
					{
						ani = MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_RIGHT;
						animation_set->at(ani)->SetCurrentFrame();
					}
					ani = MARIO_ANI_BIG_FIRE_ATTACK_ONAIR_RIGHT;
				}
					
			}
			else
			{
				if (nx < 0)
				{
					if (this->ani != MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_LEFT)
					{
						ani = MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_LEFT;
						animation_set->at(ani)->SetCurrentFrame();
					}
					ani = MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_LEFT;
				}
				else
				{
					if (this->ani != MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_RIGHT)
					{
						ani = MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_RIGHT;
						animation_set->at(ani)->SetCurrentFrame();
					}
					ani = MARIO_ANI_BIG_FIRE_ATTACK_ONGROUND_RIGHT;
				}
			}
			
		}
	}

	//Set toc do hien frame
	//isSpeedUping dang tang toc 
	if (isSpeedUping && (aniIndex == MARIO_ANI_WALKING_RIGHT || aniIndex == MARIO_ANI_WALKING_LEFT))
	{
		animation_set->at(ani)->SetHightSpeed(MARIO_RATIO_WHEN_SPEEPUPING);
	}
	else
	//Chay nhanh (dan tay truoc khi bay) 
	if (isSpeedMax && (aniIndex == MARIO_ANI_RUNNING_RIGHT || aniIndex == MARIO_ANI_RUNNING_LEFT))
	{
		animation_set->at(ani)->SetHightSpeed(MARIO_RATIO_WHEN_SPEED_MAX);
	}
	else
	//Roi va bay khi Spam S
	if (isKeepJump_SlowFalling || isKeepJump_HightFlying)
	{
		animation_set->at(ani)->SetHightSpeed(MARIO_RATIO_WHEN_KEEP_JUMPPING);
	}
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
		break;
	}
	case MARIO_STATE_RUNNING:
	{
		float ACCELERATION;
		if (!isSpeedUping)
			ACCELERATION = MARIO_WALKING_ACCELERATION;
		else
			ACCELERATION = MARIO_RUNNING_ACCELERATION;
		if (isOnAir)
		{
			SetState(MARIO_STATE_WALKING);
		}
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
			vy += MARIO_GRAVITY * dt * 10;
		}
		else
			vy += MARIO_GRAVITY * dt;
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
		break;
	}

	case MARIO_STATE_BIG_TAIL_ATTACK:
	{
		if (timeStartAttack == TIME_DEFAULT) timeStartAttack = GetTickCount();
		break;
	}
	
	//=============================END SPECIAL STATE MARIO_TAIL=============================
	
	//=============================SPECIAL STATE MARIO_FIRE=============================
	case MARIO_STATE_BIG_FIRE_ATTACK:
	{
		if (timeStartAttack == TIME_DEFAULT) timeStartAttack = GetTickCount();
		break;
	}


	case MARIO_STATE_KICK:
	{
		if (timeStartKick == TIME_DEFAULT) timeStartKick = GetTickCount();
	}
	//=============================END SPECIAL STATE MARIO_FIRE=============================
	case MARIO_STATE_STOP_RUNNING:
	{
		DecreaseSpeed(0);
		break;
	}

	case MARIO_STATE_IDLE:
	{
		if (!isOnAir)
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
	mario_general->GetBoundingBoxFromGroupAni(left, top, right, bottom, level, nx);

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
	isWalking = true;
	if (isSpeedUp)
	{
		if (vx * nx >= 0)
		{
			SetState(MARIO_STATE_RUNNING);
		}
		else
			SetState(MARIO_STATE_DECREASE_WHEN_RUNNING);
	}
	else
		SetState(MARIO_STATE_WALKING);
}


void CMario::Left()
{
	if (!isOnAir)
		isSitting = false;
	nx = -1;

}

void CMario::Right()
{
	if (!isOnAir)
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
	
	SetState(MARIO_STATE_FALLING);
	isBlockFall = false;
	////Kiem tra KeepJump
	
//	DebugOut(L"NumJump: %d", numFall);
	if (numFall >= 1)
	{
		isKeepJump = true;
	}
	numFall++;
	//DebugOut(L"NumJump sau: %d", numFall);
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

void CMario::Kick()
{
	isKicking = true;
	SetState(MARIO_STATE_KICK);
}

void CMario::SpeedUp()
{
	if (!isOnAir)
		isSpeedUp = true;
}

void CMario::HoldShell()
{
	isHoldShell = true;
}

void CMario::Sit()
{
	isSitting = true;
	SetState(MARIO_STATE_SITTING);
}

void CMario::Idle()
{
	if (vx == 0)
		isWalking = false;
	isSitting = false;
	SetState(MARIO_STATE_IDLE);
}

void CMario::Stop()
{
	isStop = true;
	SetState(MARIO_STATE_STOP_RUNNING);
}


