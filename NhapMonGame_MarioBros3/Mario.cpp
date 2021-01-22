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
	isUnTouchable = false;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	//Contructor Flag
	//Flag Scene
	isSelectMap = true;
	isGoingSelectMap = false;
	isCompleteScene = false;


	//Flage Go Selection Scene
	onPitStop = false;
	isAllowLeft = false;
	isAllowRight = false;
	isAllowUp = false;
	isAllowDown = false;
	directSelectMap = 1;
	lastIndexStop = -1;

	//Flag Other
	isGoEndScene = false;
	isDecreaseSpeed = false;
	isWalking = false;
	isOnAir = false;
	isSitting = false;
	isSpeedUping = false;
	isSpeedUp = false;
	isSpeedMax = false;
	isBlockFall = false;
	isStop = false;
	isFalling = false;
	isKeepJump_SlowFalling = false;
	isKeepJump_HightFlying = false;
	isAttacking = false;
	isKeepJump = false;
	isKicking = false;
	isKeepHoldShell = false;
	isHoldingShell = false;

	//Flag Go HideMap
	isSlideOutPipe = false;
	isInMainMap = true;
	isGoHidenMap = false;
	isOnPipeGoHideMap = false;
	isPressKeyDown = false;

	//Other
	numFall = 0;

	//Score
	numCoin = 0;
	doubleScore = false;
	changeScore = false;
	score = 100;

	//Timer
	untouchable_start;
	timeAllowFly;
	timeStartFly = TIME_DEFAULT;
	timeStartAttack = TIME_DEFAULT;
	timeStartKick = TIME_DEFAULT;

	SetState(MARIO_STATE_IDLE);
	mario_general = CMarioGeneral::GetInstance();
	mario_general->LoadListAni();

}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *listMapObj, vector<LPGAMEOBJECT>* listEnemy, vector<LPGAMEOBJECT>* listItem, vector<LPGAMEOBJECT>* listItems_Idle, vector<LPGAMEOBJECT> *listEffect, vector<LPGAMEOBJECT> *listPitStop, vector<LPGAMEOBJECT> * listFireBall)
{
#pragma region Update Mario
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (!isGoHidenMap && !isSelectMap)
		vy += MARIO_GRAVITY * dt;
	

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = TIME_DEFAULT;
		isUnTouchable = false;
	}


	//Out pipe
	if (isSlideOutPipe)
	{
		if (y + 28 < posY_of_PipeOut)
		{
			Idle();
			isSlideOutPipe = false;
		}
	}

	//Update IsFalling
	if (vy > 0)
	{
		isFalling = true;
	}

	//Update isSpeedUping 
	if (abs(vx) > MARIO_WALKING_MAX_SPEED && abs(vx) < MARIO_RUNNING_MAX_SPEED) isSpeedUping = true;
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
			if (GetTickCount() - timeStartAttack >= MARIO_TIME_BIG_TAIL_ATTACK / 2)
			{
				if (nx == 1)
					tail->SetPosition(x + 24, y + 16);
				else
					tail->SetPosition(x, y + 16);
				if (!tail->isOneKill)
					tail->canKill = true;
			}
		}
		else
		{
			if (nx == 1)
				tail->SetPosition(x, y + MARIO_D_HEED_TO_TAIL_ATTACK);
			else
				tail->SetPosition(x + MARIO_BIG_TAIL_BBOX_WIDTH + 8, y + MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->SetState(TAIL_CANNOT_KILL);
			tail->isOneKill = false;
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
					isDecreaseSpeed = true;
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
				bullet->SetPosition(x + 10, y);
				bullet->SetState(BULLET_STATE_FLY_RIGHT);
			}
			else if (nx == -1)
			{
				bullet->SetPosition(x, y);
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
	vector<LPCOLLISIONEVENT> coEnemyEvents;
	vector<LPCOLLISIONEVENT> coEnemyEventsResult;
	vector<LPCOLLISIONEVENT> coItemEvents;
	vector<LPCOLLISIONEVENT> coItemEventsResult;


	coItemEvents.clear();
	coEnemyEvents.clear();
	coObjEvents.clear();

	if (state != MARIO_STATE_DIE)
	{
		CalcPotentialCollisions(listMapObj, coObjEvents);
		CalcPotentialCollisions(listEnemy, coEnemyEvents);
		CalcPotentialCollisions(listItem, coItemEvents);
	}
	// No collision occured, proceed normally
	if (coObjEvents.size() == 0 && coEnemyEvents.size() == 0 && coItemEvents.size() == 0)
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
			//Dang Go HideMap vy #=0
			if (isGoHidenMap)
				y += dy;
			else
			{
				vy = 0;
				if (isGoEndScene)
				{
					Right();
					Go();
				}
			}	
			backup_vy = vy;
			isOnAir = false;
			isBlockFall = false;
			isKeepJump_SlowFalling = false;
			isKeepJump_HightFlying = false;
			isKeepJump = false;
			numFall = 0;

			//Va cham voi Ground thi reset Score
			doubleScore = false;
			score = 100;
		}
		else
			if (ny > 0)
			{
				if (isGoHidenMap)
					y += dy;
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
				CWeakBrick* weakbrick = dynamic_cast<CWeakBrick*>(e->obj);
				
					if (e->ny > 0)
					{
						vy = 0;
						if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_NON_ITEM)
						{
							//Dame WeakBrick Non Item
							weakbrick->Deployed_WeakBrick(listEffect); // WeakBrick destroyed -> Tao Effect
						}
						else
						if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_ITEM_P_SWITCH)
						{
							if (weakbrick->isItem)
							{
								weakbrick->SetState(WEAKBRICK_STATE_MOVE_UP);
								CExplosiveEffect* effect = new CExplosiveEffect(weakbrick->x + 2, weakbrick->y - 14);
								listEffect->push_back(effect);
							}
						}
						else
						if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_ITEM_MUSHROOM)
						{
							if (weakbrick->isItem)
								weakbrick->SetState(WEAKBRICK_STATE_MOVE_UP);
						}
						else
							if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_ITEM_COIN_EFFECT)
							{
								if (weakbrick->isItem)
								{
									weakbrick->SetState(WEAKBRICK_STATE_MOVE_UP);
								}
							}
						else if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_ITEM_TREE_LEAF)
						{
							if (weakbrick->isItem)
								weakbrick->SetState(WEAKBRICK_STATE_MOVE_UP);
						}
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
							numCoin++;
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
				if (e->ny > 0)
				{
					vy = 0;
				}
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
			CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
				if (e->nx != 0)
				{
					vx = 0;
				}
				else
				{
					float l, t, r, b;
					GetBoundingBox(l, t, r, b);
					if (e->ny < 0 && isSitting && (l - pipe->x)>4 && (pipe->x + pipe->amountX * 16) - (l + MARIO_BIG_BBOX_WIDTH) > 4)
					{
						if (pipe->isSpecial && pipe->isPullMario && pipe->isInMainMap)
							GoHiddenMap();
						posY_of_PipeIn = pipe->y;
					}
					else
						if (e->ny > 0 && (l - pipe->x) > 4 && (pipe->x + pipe->amountX * 16) - (l + MARIO_BIG_BBOX_WIDTH) > 4)
						{
							if (pipe->isSpecial && pipe->isPullMario && !pipe->isInMainMap)
								GoMainMap();
							posY_of_PipeIn = pipe->y;
						}
				}
			}
			else if (dynamic_cast<CMovingWood*>(e->obj))
			{
			CMovingWood* movingwood = dynamic_cast<CMovingWood*>(e->obj);
				if (e->nx != 0)
				{

				}
				else
					if (e->ny != 0)
					{
						if (e->ny < 0)
						{
							movingwood->SetState(MOVING_WOOD_STATE_FALLING);
						}
						else if (e->ny > 0)
						{
							vy = 0;
						}
					}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coObjEvents.size(); i++) delete coObjEvents[i];
#pragma endregion

#pragma region Colision with listEnemy
	
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
	//		y += min_ty * dy + ny * 0.1f;
		}
		else
			if (ny > 0)
			{
				if (!isUnTouchable)
					ChangeTheLevel(DETAILMARIO::CHANGE_DOWN);
			}
		for (UINT i = 0; i < coEnemyEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEnemyEventsResult[i];
			if (e->obj->type == TYPE::KOOPAS) // If obj is Koopas
			{
				if (isUnTouchable) return;
				else
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
					if (e->ny < 0) // Đạp đầu koopas
					{
						if (koopas->GetState() != KOOPAS_STATE_SLEEP)
						{
							if (koopas->level > 1)
							{
								koopas->level--;
							}
							else
								koopas->SetState(KOOPAS_STATE_SLEEP);
							Elastic();
						}
						else //Đạp mai rùa Koopas
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
						//Create Effect Coin
						CreateEffectCoin(listEffect);
					}
					else if (e->nx != 0)
					{
						if (koopas->GetState() != KOOPAS_STATE_SLEEP) //Koopas not sleep -> Decreee Level
						{
							ChangeTheLevel(DETAILMARIO::CHANGE_DOWN);
						}
						else
						{
							if (!isKeepHoldShell) // No Keep A -> Kick Koopas
							{
								koopas->isHeld = false;
								Kick();
								if (nx < 0) koopas->nx = 1;
								else
									koopas->nx = -1;
								koopas->isKicked = true;
								koopas->SetState(KOOPAS_STATE_MOVING);
							}
							else //Held Koopas
							{
								isHoldingShell = true;
								koopas->isHeld = true;
							}
						}
					}
				}
			} // if Goomba
			else
				if (e->obj->type == TYPE::GOOMBA) // if e->obj is Goomba 
				{
					if (isUnTouchable) return;
					else
					{
						CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
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
								Elastic();
								//Create Effect Coin
								CreateEffectCoin(listEffect);
							}
						}
						else if (e->nx != 0)
						{
							if (isUnTouchable == 0)
							{
								if (goomba->GetState() != GOOMBA_STATE_DIE)
								{
									ChangeTheLevel(DETAILMARIO::CHANGE_DOWN);
								}
							}
						}
					}
				}
				else if (e->obj->type == FLOWER)
				{
					if (isUnTouchable) return;
					else
					{
						CFlower* flower = dynamic_cast<CFlower*>(e->obj);
						if (flower->GetState() != GOOMBA_STATE_DIE)
						{
							if (e->nx != 0 || e->ny != 0)
							{
								if (!flower->isSleep)
									ChangeTheLevel(DETAILMARIO::CHANGE_DOWN);

							}
						
						}
					}
				}
				else if (e->obj->type == BOOMERANG_BROTHER)
				{
					if (isUnTouchable)
						return;
					else
					{
						CBomerangBrother *brother = dynamic_cast<CBomerangBrother*>(e->obj);
						if (e->ny < 0)
						{
							brother->SetState(BOMERANGBROTHER_STATE_DIE);
							CreateEffectCoin(listEffect);
							Elastic();
						}
					}
				}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEnemyEvents.size(); i++) delete coEnemyEvents[i];
#pragma endregion

#pragma region Collision with listFireBall
	for (int i = 0; i < listFireBall->size(); i++)
	{
		if (isCollisionWithObj(listFireBall->at(i)))
		{
			if (!isUnTouchable) 
				ChangeTheLevel(DETAILMARIO::CHANGE_DOWN);
		}
	}
#pragma endregion

#pragma region Colision with listItem
//P_Switch
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
					Elastic();
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
					CMushroom* mushroom = dynamic_cast<CMushroom*>(listItem->at(i));
				
					if (mushroom->isComplete)
					{
						if (mushroom->color == MUSHROOM_RED)
						{
							level = MARIO_LEVEL_BIG;
						}
						listItem->at(i)->isActive = false;
					}
				}
				else
				if (listItem->at(i)->type == TYPE::LEAF_TREE)
				{
					CLeafTree* leaftree = dynamic_cast<CLeafTree*>(listItem->at(i));
					if (leaftree->isComplete)
					{
						level = MARIO_LEVEL_BIG_TAIL;
						listItem->at(i)->isActive = false;
					}
				}
				else
				if (listItem->at(i)->type == TYPE::COIN_IDLE_STATIC || listItem->at(i)->type == TYPE::COIN_IDLE_SPIN)
				{
					numCoin++;
					listItem->at(i)->isActive = false;
				}
				else
					if (listItem->at(i)->type == TYPE::ITEM_END_GAME)
					{
						CItemEndScence* itemEndScence = dynamic_cast<CItemEndScence*>(listItem->at(i));
						itemEndScence->SetState(ITEM_ENDGAME_STATE_USED);
						DecreaseSpeed(MARIO_WALKING_ACCELERATION);
						GoEndScence();
					}
			}
		}
	}
	for (int i = 0; i < listItems_Idle->size(); i++)
	{
		if (listItems_Idle->at(i) != NULL)
		{
			if (isCollisionWithObj(listItems_Idle->at(i)))
			{
						if (listItems_Idle->at(i)->type == TYPE::COIN_IDLE_STATIC || listItems_Idle->at(i)->type == TYPE::COIN_IDLE_SPIN)
						{
							numCoin++;
							listItems_Idle->at(i)->isActive = false;
						}
						else
							if (listItems_Idle->at(i)->type == TYPE::ITEM_END_GAME)
							{
								CItemEndScence* itemEndScence = dynamic_cast<CItemEndScence*>(listItems_Idle->at(i));
								itemEndScence->SetState(ITEM_ENDGAME_STATE_USED);
								DecreaseSpeed(MARIO_WALKING_ACCELERATION);
								GoEndScence();
							}
			}
		}
	}//Coin Idle Spin And Item End Scene

#pragma endregion
	  
#pragma region Collision with Portal
	for (int i = 0; i < listPitStop->size(); i++)
	{
		if (listPitStop->at(i) != NULL)
		{
			if (isCollisionWithObj(listPitStop->at(i)))
			{
				if (listPitStop->at(i)->type == TYPEPITSTOP::PITSTOP)
				{
					CPitStop* pitStop = dynamic_cast<CPitStop*>(listPitStop->at(i));
					isAllowLeft = pitStop->isAllowLeft;
					isAllowRight = pitStop->isAllowRight;
					isAllowUp = pitStop->isAllowUp;
					isAllowDown = pitStop->isAllowDown;

					if (i != lastIndexStop)
					{
						switch (directSelectMap)
						{
						case DIRECT_RIGHT:
							if (x > pitStop->x)
							{
								x = pitStop->x;
								lastIndexStop = i;
								vx = 0;
							}
							break;
						case DIRECT_LEFT:
							if (x < pitStop->x)
							{
								x = pitStop->x;
								lastIndexStop = i;
								vx = 0;
							}
							break;
						case DIRECT_UP:
							if (y < pitStop->y)
							{
								y = pitStop->y;
								lastIndexStop = i;
								vy = 0;
							}
							break;
						case DIRECT_DOWN:
							if (y > pitStop->y)
							{
								y = pitStop->y;
								lastIndexStop = i;
								vy = 0;
							}
							break;
						}
						if (lastIndexStop == i)
							isGoingSelectMap = false;
					}
					
				}
				else
					if (listPitStop->at(i)->type == TYPEPITSTOP::PORTAL)
					{
						CPortal* portal = dynamic_cast<CPortal*>(listPitStop->at(i));
						isAllowLeft = portal->isAllowLeft;
						isAllowRight = portal->isAllowRight;
						isAllowUp = portal->isAllowUp;
						isAllowDown = portal->isAllowDown;
						//Khi va cham vs portal thi di vo chinh giua
						if (i != lastIndexStop)
						{
							switch (directSelectMap)
							{
							case DIRECT_RIGHT:
								if (x > portal->x)
								{
									x = portal->x;
									lastIndexStop = i;
									vx = 0;
									vy = 0;
								}
								break;
							case DIRECT_LEFT:
								if (x < portal->x)
								{
									x = portal->x;
									lastIndexStop = i;
									vx = 0;
									vy = 0;
								}
								break;
							case DIRECT_UP:
								if (y < portal->y)
								{
									y = portal->y;
									lastIndexStop = i;
									vx = 0;
									vy = 0;
								}
								break;
							case DIRECT_DOWN:
								if (y > portal->y)
								{
									y = portal->y;
									lastIndexStop = i;
									vx = 0;
									vy = 0;
								}
								break;
							}
							if (lastIndexStop == i)
								isGoingSelectMap = false;
							
						}
						if (isSelectMap)
						{
							if (isPressKeyDown)
							{
								CGame::GetInstance()->SwitchScene(portal->GetSceneId());
								portalPre = portal;
								isPressKeyDown = false;
								isSelectMap = false;
								lastIndexStop = i;
							}
						}
						else if (!isSelectMap)
						{
							isCompleteScene = true;
							portalReturn = portal;
							vx = 0;
							vy = 0;
						}
						
					}
			
				
			}
		}
	}
#pragma endregion
}

void CMario::Render()
{
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else
		ani = RenderFromAniGroup();
	int alpha = 255;
	if (isUnTouchable) alpha = rand() % (200 - 50 + 1) + 50;
	animation_set->at(ani)->Render(x, y, alpha);
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
	if (isGoHidenMap)
	{
		aniIndex = MARIO_ANI_GO_HIDDEN_MAP;
		ani = mario_general->GetAni_Mario(level, aniIndex);
	}
	if (isSelectMap)
	{
		aniIndex = MARIO_ANI_SELECT_MAP;
		ani = mario_general->GetAni_Mario(level, aniIndex);
	}
	return ani;
}

void CMario::CreateEffectCoin(vector<LPGAMEOBJECT>* listEffect)
{
	//Create Effect Coin
	if (doubleScore)
		score *= 2;
	doubleScore = true;
	CScoreEffect* scoreEffect = new CScoreEffect(x, y);
	scoreEffect->SetScore(score);
	changeScore = true;
	listEffect->push_back(scoreEffect);
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
	isDecreaseSpeed = true;
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
	case MARIO_STATE_ELASETIC:
	{
		vy = -MARIO_ELASETIC_SPEED_Y;
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
	case MARIO_STATE_GO_SELECT_MAP:
	{
		switch (directSelectMap)
		{
		case 1:
			vx = MARIO_SPEED_SELECT_MAP;
			break;
		case 2:
			vx = -MARIO_SPEED_SELECT_MAP;
			break;
		case 3:
			vy = -MARIO_SPEED_SELECT_MAP;
			break;
		case 4:
			vy = MARIO_SPEED_SELECT_MAP;
			break;
	/*	default:
			SetPosition(portalPre->x, portalPre->y);
			break;*/
		}
		break;
	}
	case MARIO_STATE_GO_ENDSCENCE:
	{
		vx = 0;
		vy = 0;
		break;
	}
	case MARIO_STATE_GO_HIDDEN_MAP:
	{
		vx = 0;
		vy = 0.02f;
		break;
	}
	case MARIO_STATE_GO_MAIN_MAP:
	{
		vx = 0;
		vy = -0.02f;
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

void CMario::ChangeTheLevel(int typeChange)
{
	if (typeChange == DETAILMARIO::CHANGE_DOWN)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			vx = 0;
			Elastic();
			SetState(MARIO_STATE_DIE);
		}

		
	}
	else
	{
		if (level < MARIO_LEVEL_BIG_FIRE)
			level++;
	}
}

void CMario::SetOnMap(bool isSelectMap)
{
	this->isSelectMap = isSelectMap;
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

CMario* CMario::__instance = NULL;
CMario* CMario::GetInstance()
{
	if (__instance == NULL) __instance = new CMario();
	return __instance;
}

void CMario::Elastic()
{
	isOnAir = true;
	isFalling = false;
	SetState(MARIO_STATE_ELASETIC);
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
	isOnAir = true;
	isGoHidenMap = false;
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
	isKeepHoldShell = true;
}

void CMario::GoHiddenMap()
{
	isGoHidenMap = true;
	SetState(MARIO_STATE_GO_HIDDEN_MAP);
}

void CMario::GoMainMap()
{
	isGoHidenMap = true;
	SetState(MARIO_STATE_GO_MAIN_MAP);
}

void CMario::GoSelectMap()
{
	isSelectMap = true;
	isGoingSelectMap = true;
	SetState(MARIO_STATE_GO_SELECT_MAP);
}

void CMario::GoEndScence()
{
	isGoEndScene = true;
	Right();
	SetState(MARIO_STATE_GO_ENDSCENCE);
}

void CMario::Sit()
{
	isSitting = true;
	SetState(MARIO_STATE_SITTING);
}

void CMario::Idle()
{
	isGoHidenMap = false;
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


