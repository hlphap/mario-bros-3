#include "Koopas.h"
#include "ColorBox.h"
#include "Utils.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "ScoreEffect.h"
#include "Flower.h"
#include "WeakBrick.h"
#include "Brick.h"

CKoopas::CKoopas(CMario* m, float x, float y, int type, int level)
{
	this->type = TYPE::KOOPAS;
	this->category = CATEGORY::ENEMY;
	nx = -1;
	this->typeColor = type;
	this->level = level;
	minY = y;
	maxY = y + 40.0f; //Koopas red fly
	player = m;
	SetState(KOOPAS_STATE_MOVING);
	if (level == KOOPAS_LEVEL_HAVE_WING)
	{
		if (typeColor == KOOPAS_TYPE_RED)
		{
			vy = KOOPAS_FLYING_SPEED_Y;
		}
	}
	koopasGeneral = CKoopasGeneral::GetInstance();
	koopasGeneral->LoadListAni();
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
	if (isSleeping)	
		top = top + KOOPAS_BBOX_HEIGHT_SLEEP;
	
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
			player->isHoldingShell = false;
		}
		nx = -player->nx;
		SetState(KOOPAS_STATE_MOVING);
		isHeal = false;
		isPreHeal = false;
	}
	else
		if (state == KOOPAS_STATE_SLEEP && timeStartSleep != 0 && GetTickCount() - timeStartSleep >= 4000)	//Co chan
		{
			isHeal = true;
			isPreHeal = false;
		}
		else
		if (state == KOOPAS_STATE_SLEEP && timeStartSleep != 0 && GetTickCount() - timeStartSleep >= 3000) // Khong chan
		{
			isHeal = false;
			isPreHeal = true;
		}
	//Bi cam thi khong co gia toc trong truong
	//Bị cầm  ->> Koopas follow Mario
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
				rangeX = -KOOPAS_BBOX_WIDTH + 5 + 10;
			else
				rangeX = MARIO_BIG_BBOX_WIDTH - 3 + 10;
			rangeY = 2;
		}
		else if (player->level == MARIO_LEVEL_BIG_TAIL)
		{
			if (player->nx < 0)
				rangeX = -KOOPAS_BBOX_WIDTH + 5 + 8;
			else
				rangeX = MARIO_BIG_TAIL_BBOX_WIDTH - 8 + 11;
			rangeY = 1;
		}
		else if (player->level == MARIO_LEVEL_SMALL)
		{
			if (player->nx < 0)
				rangeX = -KOOPAS_BBOX_WIDTH + 5 + 11;
			else
				rangeX = MARIO_SMALL_BBOX_WIDTH - 4 + 11;
			rangeY = -2;
		}
		SetPosition(player->x + rangeX, player->y - rangeY);
		return;
	}

	if (level == KOOPAS_LEVEL_HAVE_WING)
	{
		if (typeColor == KOOPAS_TYPE_RED)
		{
			if (y < minY)
			{
				vy = KOOPAS_FLYING_SPEED_Y;
			}
			if (y > maxY)
			{
				vy = -KOOPAS_FLYING_SPEED_Y;
			}
		}
	}
//	DebugOut(L"\nkooasp->isFaling: %d", koopasAi->isFalling);
	if (level == KOOPAS_LEVEL_DEFAULT)
	{
		if (typeColor == KOOPAS_TYPE_RED)
		{
			if (nx == 1)
			{
				koopasAi->SetPosition(x + 5, y);
				if (koopasAi->isFalling)
				{
					nx = -1;
					koopasAi->SetPosition(x - 15, y);
					SetState(KOOPAS_STATE_MOVING);
				}
			}
			else if (nx == -1)
				{
				
					koopasAi->SetPosition(x - 10, y);
					if (koopasAi->isFalling)
					{
					
						nx = 1;
						koopasAi->SetPosition(x +5, y);
						SetState(KOOPAS_STATE_MOVING);
					}
				}
			
		}
	}
	if (koopasAi!=NULL)
		koopasAi->Update(dt, coObjects);
	CGameObject::Update(dt);
	if (!(typeColor == KOOPAS_TYPE_RED && level== KOOPAS_LEVEL_HAVE_WING))
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
					if (!isSleeping && level != KOOPAS_LEVEL_HAVE_WING && typeColor==KOOPAS_TYPE_RED)
					{
						if (x <= colorbox->x - BRICK_BBOX_WIDTH + 6)
						{
							x = colorbox->x;
							this->nx = 1;
						}
						else if (x + KOOPAS_BBOX_WIDTH >= colorbox->x + colorbox->amountX * BRICK_BBOX_WIDTH + BRICK_BBOX_WIDTH - 6)
						{
							x = colorbox->x + colorbox->amountX * BRICK_BBOX_WIDTH - KOOPAS_BBOX_WIDTH;
							this->nx = -1;
						}
					}
				}
			}
			else
			if (dynamic_cast<CWeakBrick*>(e->obj))
			{
				CWeakBrick* weakBrick = dynamic_cast<CWeakBrick*>(e->obj);
				if (e->nx != 0)
				{
					weakBrickDeployed = weakBrick;
					if (e->nx > 0)
					{
						this->nx = 1;
					}
					else if (e->nx < 0)
						this->nx = -1;
				}
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				CGround* ground = dynamic_cast<CGround*>(e->obj);
				if (e->nx > 0)
				{
					this->nx = 1;
				}
				else if (e->nx < 0)
					this->nx = -1;
				else
				if (e->ny < 0)
				{
					if (!isSleeping && level != KOOPAS_LEVEL_HAVE_WING && typeColor == KOOPAS_TYPE_RED)
					{
						if (x <= ground->x - BRICK_BBOX_WIDTH + 6)
						{
							x = ground->x;
							this->nx = 1;
						}
						else if (x + KOOPAS_BBOX_WIDTH >= ground->x + ground->amountX * BRICK_BBOX_WIDTH + BRICK_BBOX_WIDTH - 6)
						{
							x = ground->x + ground->amountX * BRICK_BBOX_WIDTH - KOOPAS_BBOX_WIDTH;
							this->nx = -1;
						}
					}
				}
			}
			else if (dynamic_cast<CQuestionBrick*>(e->obj))
			{
				CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
				if (e->nx != 0)
				{
					this->questionBrick = questionBrick;
					if (e->nx > 0)
					{
						this->nx = 1;
					}
					else if (e->nx < 0)
						this->nx = -1;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx > 0)
				{
					this->nx = 1;
				}
				else if (e->nx < 0)
					this->nx = -1;
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
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::IsCollisionWhenShellMove(vector<LPGAMEOBJECT>* listMapObj, vector<LPGAMEOBJECT>* listEnemies, vector<LPGAMEOBJECT> *listEffects)
{
	if (isSleeping && isMoving || isHeld)
	{
		for (size_t i = 0; i < listEnemies->size(); i++)
		{
			if (isCollisionWithObj(listEnemies->at(i)))
			{
				if (listEnemies->at(i)->type == TYPE::GOOMBA)
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(listEnemies->at(i));
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->isKillByWeapon = true;
						goomba->SetState(GOOMBA_STATE_DIE);

						//Create Effect Coin
						CScoreEffect* effectScore = new CScoreEffect(goomba->x, goomba->y);
						CImpactEffect* effectIm = new CImpactEffect(goomba->x, goomba->y);
						listEffects->push_back(effectScore);
						listEffects->push_back(effectIm);
					}
					player->isHoldingShell = false;
				}
				if (listEnemies->at(i)->type == TYPE::FLOWER)
				{
					CFlower* flower = dynamic_cast<CFlower*>(listEnemies->at(i));
					if (flower->GetState() != FLOWER_STATE_DIE)
					{
						flower->SetState(FLOWER_STATE_DIE);
						CScoreEffect* effectScore = new CScoreEffect(flower->x, flower->y);
						CExplosiveEffect* effectIm = new CExplosiveEffect(flower->x, flower->y);
						listEffects->push_back(effectScore);
						listEffects->push_back(effectIm);
					}
					player->isHoldingShell = false;
				}
				if (listEnemies->at(i)->type == TYPE::KOOPAS)
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(listEnemies->at(i));
					if (koopas->GetState() != KOOPAS_STATE_DIE && koopas != this)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
						CScoreEffect* effectScore = new CScoreEffect(koopas->x, koopas->y);
						CExplosiveEffect* effectIm = new CExplosiveEffect(koopas->x, koopas->y);
						listEffects->push_back(effectScore);
						listEffects->push_back(effectIm);
						player->isHoldingShell = false;
					}
				}
			}
		} //Va cham vs Enemies
		if (weakBrickDeployed != NULL)
		{
			if (weakBrickDeployed->typeWeakBrick == WEAKBRICK_TYPE_NON_ITEM)
			{
				//Dame WeakBrick Non Item
				weakBrickDeployed->Deployed_WeakBrick(listEffects); // WeakBrick destroyed -> Tao Effect
			}
			else
				if (weakBrickDeployed->typeWeakBrick == WEAKBRICK_TYPE_ITEM_P_SWITCH)
				{
					if (weakBrickDeployed->isItem)
					{
						weakBrickDeployed->SetState(WEAKBRICK_STATE_MOVE_UP);
						CExplosiveEffect* effect = new CExplosiveEffect(weakBrickDeployed->x + 2, weakBrickDeployed->y - 14);
						listEffects->push_back(effect);
					}
				}
				else
					if (weakBrickDeployed->typeWeakBrick == WEAKBRICK_TYPE_ITEM_MUSHROOM)
					{
						if (weakBrickDeployed->isItem)
							weakBrickDeployed->SetState(WEAKBRICK_STATE_MOVE_UP);
					}
					else
						if (weakBrickDeployed->typeWeakBrick == WEAKBRICK_TYPE_ITEM_COIN_EFFECT)
						{
							if (weakBrickDeployed->isItem)
							{
								weakBrickDeployed->SetState(WEAKBRICK_STATE_MOVE_UP);
							}
						}
			weakBrickDeployed = NULL;
		}
		if (questionBrick != NULL)
		{
			if (questionBrick->isItem)
			{
				//Update typeQuestion
				if (questionBrick->typeQuestion == QUESTION_TYPE_COIN)
				{
					questionBrick->typeItem = ITEM_LEVEL_COIN;
					player->numCoin++;
				}
				else
				{
					if (player->level == MARIO_LEVEL_SMALL)
						questionBrick->typeItem = ITEM_LEVEL_MUSHROOM;
					else
						if (player->level == MARIO_LEVEL_BIG)
						{
							questionBrick->typeItem = ITEM_LEVEL_TREE_LEAF;
						}
						else
							questionBrick->typeItem = ITEM_LEVEL_TREE_LEAF;
				}
				questionBrick->SetState(QUESTION_STATE_MOVE_UP);
			}
		}
	}

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
			if (typeColor == KOOPAS_TYPE_GREEN)
			{
				vy = -KOOPAS_SPEED_BOUNCE;
				if (nx > 0)
				{
					vx = KOOPAS_WALKING_SPEED;
				}
				else
					vx = -KOOPAS_WALKING_SPEED;
			}
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
		if (!isKillByWeapon) // overturned
		{
			if (isPreHeal)
			{
				aniIndex = KOOPAS_ANI_SHELL_REVIAL_KHONGCHAN;
			}
			else
				if (isHeal)
				{
					aniIndex = KOOPAS_ANI_SHELL_REVIAL_COCHAN;
				}
				else
					aniIndex = KOOPAS_ANI_SHELL_IDLE;
		}
		else
			if (isPreHeal)
			{
				aniIndex = KOOPAS_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN;
			}
			else
				if (isHeal)
				{
					aniIndex = KOOPAS_ANI_SHELL_OVERTURNED_REVIAL_COCHAN;
				}
				else
					aniIndex = KOOPAS_ANI_SHELL_OVERTURNED_IDLE;

	ani = koopasGeneral->GetAni_Koopas(typeColor, aniIndex);
	//	DebugOut(L"Koopas Ani %d", ani);
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();




}