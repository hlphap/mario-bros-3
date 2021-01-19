#include "Bullet.h"
#include "Pipe.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "CloudBrick.h"
#include "ColorBox.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Utils.h"
#include "WeakBrick.h"
#include "Flower.h"
#include "ScoreEffect.h"
#include "BomerangBrother.h"

CBullet::CBullet()
{
	isActive = true;
	vy = BULLET_FLY_SPEED_Y;
	animation_set = CAnimationSets::GetInstance()->Get(7);
}

void CBullet::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_WIDTH;
}
void CBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_FLY_LEFT:
	{
		vx = -BULLET_FLY_SPEED_X ;
		vy = BULLET_FLY_SPEED_Y;
		break;
	}

	case BULLET_STATE_FLY_RIGHT:
	{
		vx = BULLET_FLY_SPEED_X;
		vy = BULLET_FLY_SPEED_Y;
		break;
	}
	case BULLET_STATE_EXPLOSIVE:	
	{
		vx = 0;
		vy = 0;
		break;
	}
	}
}
void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj,vector<LPGAMEOBJECT> *listEnemy, vector<LPGAMEOBJECT> *listEffect)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	vy += BULLET_GRAVITY * dt;
	if (vy > BULLET_FLY_SPEED_Y) vy = BULLET_FLY_SPEED_Y;
	else
	if (vy < -BULLET_FLY_SPEED_Y) vy = -BULLET_FLY_SPEED_Y;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	if (state != BULLET_STATE_EXPLOSIVE)
		CalcPotentialCollisions(listMapObj, coEvents);
	else
	{
		effect = new CExplosiveEffect(x, y);
		listEffect->push_back(effect);
		isActive = false;
	}



#pragma region ColisionWithMapObj
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// Brick defaul
			if (dynamic_cast<CColorBox*>(e->obj))
			{
				if (e->ny != 0)
				{
					vy = -vy;
				}
				x += dx;
			}
			else if(dynamic_cast<CGround*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
				
			}
			else if (dynamic_cast<CPipe*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
				else
					if (isCollisionWithObj(e->obj))
					{
						SetState(BULLET_STATE_EXPLOSIVE);
					}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
			}
			else if (dynamic_cast<CQuestionBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
			}
			else if (dynamic_cast<CCloudBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
			}
			else if (dynamic_cast<CWeakBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(BULLET_STATE_EXPLOSIVE);
				}
				if (e->ny != 0)
				{
					vy = -vy;
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	
#pragma endregion

#pragma region ColisionWithEnemy
	for (int i = 0; i < listEnemy->size(); i++)
	{
		if (listEnemy->at(i)->type == GOOMBA)
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(listEnemy->at(i));
			if (isCollisionWithObj(goomba))
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					goomba->isKillByWeapon = true;
					goomba->SetState(GOOMBA_STATE_DIE);
					SetState(BULLET_STATE_EXPLOSIVE);

					//Create Effect Coin
					CScoreEffect* effect = new CScoreEffect(goomba->x, goomba->y);
					listEffect->push_back(effect);
				}
			}
		}
		else if (listEnemy->at(i)->type == KOOPAS)
		{
			CKoopas* koopas = dynamic_cast<CKoopas*>(listEnemy->at(i));
			if (isCollisionWithObj(koopas))
			{
				if (koopas->GetState() != KOOPAS_STATE_DIE)
				{
					koopas->isKillByWeapon = true;
					koopas->SetState(KOOPAS_STATE_DIE);
					koopas->vy = -KOOPAS_JUMP_DEFLECT_SPEED;
					SetState(BULLET_STATE_EXPLOSIVE);
					//Create Effect Coin
					CScoreEffect* effect = new CScoreEffect(koopas->x, koopas->y);
					listEffect->push_back(effect);
				}
			}
		}
		else if (listEnemy->at(i)->type == FLOWER)
		{
			CFlower* flower = dynamic_cast<CFlower*>(listEnemy->at(i));
			if (isCollisionWithObj(flower))
			{
				flower->SetState(FLOWER_STATE_DIE);
				SetState(BULLET_STATE_EXPLOSIVE);
				//Create Effect Coin
				CScoreEffect* effect = new CScoreEffect(flower->x, flower->y);
				listEffect->push_back(effect);
			}
		}
		else if (listEnemy->at(i)->type == TYPE::BOOMERANG_BROTHER)
		{
			CBomerangBrother* brother = dynamic_cast<CBomerangBrother*>(listEnemy->at(i));
			if (isCollisionWithObj(brother))
			{
				brother->SetState(BOMERANGBROTHER_STATE_DIE);
				SetState(BULLET_STATE_EXPLOSIVE);
				CScoreEffect* effect = new CScoreEffect(brother->x, brother->y);
				brother->isActive = false;
			}
		}
	}
#pragma endregion
}
