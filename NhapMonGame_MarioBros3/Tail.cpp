#include "Tail.h"
#include "Utils.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopas.h"
#include "WeakBrick.h"
#include "QuestionBrick.h"
#include "Switch_P.h"
#include "Flower.h"
#include "BomerangBrother.h"

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

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT> *listMapObj, vector<LPGAMEOBJECT>* listEnemy, vector<LPGAMEOBJECT> *listItem, vector<LPGAMEOBJECT> *listEffect)
{
	CGameObject::Update(dt);
#pragma region Collision with Enemy
	for (UINT i = 0; i < listEnemy->size(); i++)
	{
		if (isCollisionWithObj(listEnemy->at(i)))
		{
			if (listEnemy->at(i)->type == TYPE::GOOMBA)
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(listEnemy->at(i));
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					if (canKill)
					{
						effect = new CImpactEffect(goomba->x, goomba->y);
						listEffect->push_back(effect);
						goomba->isKillByWeapon = true;
						goomba->SetState(GOOMBA_STATE_DIE);
					}
				}
			}
			else
				if (listEnemy->at(i)->type == TYPE::KOOPAS)
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(listEnemy->at(i));
					if (canKill)
					{
						if (koopas->GetState() != KOOPAS_STATE_DIE && koopas->vy > 0)
						{
							effect = new CImpactEffect(koopas->x, koopas->y);
							listEffect->push_back(effect);
							koopas->SetState(KOOPAS_STATE_SLEEP);
							koopas->vy = -KOOPAS_JUMP_DEFLECT_SPEED;
							/*if (this->nx == 1)
								koopas->vx = 0.1f;
							else
								koopas->vx = -0.1f;*/
							koopas->isKillByWeapon = true;
							koopas->timeStartSleep = GetTickCount();
							koopas->isHeal = false;
							koopas->isPreHeal = false;	
							canKill = false;
							isOneKill = true;
							DebugOut(L"\nCreateEffect");
						}
					}
				}
				else
					if (listEnemy->at(i)->type == TYPE::FLOWER)
					{
						CFlower* flower = dynamic_cast<CFlower*>(listEnemy->at(i));
						if (flower->GetState() != FLOWER_STATE_DIE)
						{
							if (canKill)
							{
								effect = new CImpactEffect(flower->x, flower->y);
								listEffect->push_back(effect);
								flower->isKillByWeapon = true;
								flower->SetState(FLOWER_STATE_DIE);
							}
						}
					}
					else if (listEnemy->at(i)->type == TYPE::BOOMERANG_BROTHER)
					{
						CBomerangBrother* brother = dynamic_cast<CBomerangBrother*>(listEnemy->at(i));
						brother->SetState(BOMERANGBROTHER_STATE_DIE);
						effect = new CImpactEffect(brother->x, brother->y);
						brother->vy = -0.1f;
					}
		}
	}
#pragma endregion

#pragma region Collision with MapObj
	for (int i = 0; i < listMapObj->size(); i++)
	{
		if (listMapObj->at(i) != NULL)
		{
			if (isCollisionWithObj(listMapObj->at(i)))
			{
				if (this->canKill)
				{
					if (listMapObj->at(i)->type == TYPE::WEAK_BRICK)
					{
						CWeakBrick* weakbrick = dynamic_cast<CWeakBrick*>(listMapObj->at(i));
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
						else if (weakbrick->typeWeakBrick == WEAKBRICK_TYPE_ITEM_TREE_LEAF)
						{
							if (weakbrick->isItem)
								weakbrick->SetState(WEAKBRICK_STATE_MOVE_UP);
						}
						isOneKill = true;
						canKill = false;
					}
					else
					if (listMapObj->at(i)->type == TYPE::QUESTION_BRICK)
					{
						//Dame QuestionBrick
						CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(listMapObj->at(i));
						if (questionBrick->isItem)
						{
							//Update typeQuestion
							if (questionBrick->typeQuestion == QUESTION_TYPE_COIN)
							{
								questionBrick->typeItem = ITEM_LEVEL_COIN;
							}
							else
							{
								questionBrick->typeItem = ITEM_LEVEL_TREE_LEAF;
							}
							questionBrick->SetState(QUESTION_STATE_MOVE_UP);
						}
						isOneKill = true;
					}
				}
			}
		}
	}

#pragma endregion

	
}

CTail* CTail::__instance = NULL;
CTail* CTail::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CTail();
	}
	return __instance;
}