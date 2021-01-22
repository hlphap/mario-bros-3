#include "Flower.h"
#include "Utils.h"
#include "PlayScence.h"



CFlower::CFlower(CMario* m, int type)
{
	this->type = TYPE::FLOWER;
	player = m;
	this->typeColor = type;
	this->start_y = 0;
	isPause = false;
	ny = 1;
	SetState(FLOWER_STATE_MOVE_TO_ATTACK);
	if (typeColor == FLOWER_TYPE_RED)
	{
		height = FLOWER_RED_BBOX_HEIGHT;
	}
	else if (typeColor == FLOWER_TYPE_GREEN)
	{
		height = FLOWER_GREEN_BBOX_HEIGHT;
	}
	else if (typeColor == FLOWER_TYPE_GREEN_BITE)
	{
		height = FLOWER_GREEN_BITE_BBOX_HEIGHT;
	}
}

void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (typeColor == FLOWER_TYPE_RED)
	{
		r = x + FLOWER_RED_BBOX_WIDTH;
		b = y + FLOWER_RED_BBOX_HEIGHT;
	//	height = FLOWER_RED_BBOX_HEIGHT;
	}
	else if (typeColor == FLOWER_TYPE_GREEN)
	{
		r = x + FLOWER_GREEN_BBOX_WIDTH;
		b = y + FLOWER_GREEN_BBOX_HEIGHT;
		//height = FLOWER_GREEN_BBOX_HEIGHT;
	}
	else if (typeColor == FLOWER_TYPE_GREEN_BITE)
	{
		r = x + FLOWER_GREEN_BITE_BBOX_WIDTH;
		b = y + FLOWER_GREEN_BITE_BBOX_HEIGHT;
		//height = FLOWER_GREEN_BITE_BBOX_HEIGHT;
	}
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt,coObjects);
	
	//Cập nhật hướng Hoa
	if (player->x < x)
		nx = -1;
	else
		nx = 1;
	if (player->y < y)
		ny = 1;
	else
		ny = -1;

	//Cập nhật start_y
	if (start_y == 0)
	{
		start_y = y;
	}

	//Chuyen State
	//DebugOut(L"y: %d\n", GetTickCount() - timeStartAttack);
	if (!isMoveAttack && GetTickCount() - timeStartAttack >= 7000 && timeStartAttack != TIME_DEFAULT)
	{
		SetState(FLOWER_STATE_MOVE_TO_ATTACK);
		timeStartAttack = TIME_DEFAULT;
		isSleep = false;
		//Bay len ban
	}
	else
	if (!isAttack && GetTickCount() - timeStartAttack >= 3000 && timeStartAttack!= TIME_DEFAULT)
	{
		SetState(FLOWER_STATE_MOVE_TO_RETIRE);
		//Rut Lui
	}
	else
		if (isAttack && GetTickCount() - timeStartAttack >= 1000 && timeStartAttack != TIME_DEFAULT)
		{
			if (typeColor != FLOWER_TYPE_GREEN_BITE)
			{
				isCreateFireBall = true;
			}
			else
				timeStartAttack += 1000;
			isAttack = false;
			//Bans
		}
	//Giới hạn 
	if (isMoveAttack)
	{
		if (y + height < start_y)
		{
			y = start_y - height;
			SetState(FLOWER_STATE_IDLE);
			isAttack = true;
		}
	}
	else
	{
		if (y >= start_y)
		{
			y = start_y;
			isSleep = true;
			SetState(FLOWER_STATE_IDLE);
		}
	}

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
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.1f;

	//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//}
}


void CFlower::SetState(int state)
{
	
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_MOVE_TO_ATTACK:
		isMoveAttack = true;
		vy = -0.045;
		break;
	case FLOWER_STATE_MOVE_TO_RETIRE:
		isMoveAttack = false;
		vy = 0.045;
		break;
	case FLOWER_STATE_IDLE:
	{
		if (isMoveAttack)
			timeStartAttack = GetTickCount();
		vy = 0.0f;
		break;
	}
	case FLOWER_STATE_ATTACK:
		vy = 0;
		break;
	case FLOWER_STATE_DIE:
		isActive = false;
		isMoveAttack = false;
	}
}


void CFlower::Render()
{
	//RenderBoundingBox();
	int ani = -1;
	if (typeColor == FLOWER_TYPE_RED)
	{
		if (nx == 1)
		{
			if (ny == 1)
			{
				if (isAttack)
					ani = FLOWER_RED_ANI_ATTACK_UPPER_RIGHT;
				else
					ani = FLOWER_RED_ANI_MOVE_UPPER_RIGHT;
			}
			else
			{
				if (isAttack)
					ani = FLOWER_RED_ANI_ATTACK_BOTTOM_RIGHT;
				else
					ani = FLOWER_RED_ANI_MOVE_BOTTOM_RIGHT;
			}

		}
		else if (nx == -1)
		{
			if (ny == 1)
			{
				if (isAttack)
					ani = FLOWER_RED_ANI_ATTACK_UPPER_LEFT;
				else
					ani = FLOWER_RED_ANI_MOVE_UPPER_LEFT;
			}
			else
			{
				if (isAttack)
					ani = FLOWER_RED_ANI_ATTACK_BOTTOM_LEFT;
				else
					ani = FLOWER_RED_ANI_MOVE_BOTTOM_LEFT;
			}
		}
	}
	else
		if (typeColor == FLOWER_TYPE_GREEN)
		{
			if (nx == 1)
			{
				if (ny == 1)
				{
					if (isAttack)
						ani = FLOWER_GREEN_ANI_ATTACK_UPPER_RIGHT;
					else
						ani = FLOWER_GREEN_ANI_MOVE_UPPER_RIGHT;
				}
				else
				{
					if (isAttack)
						ani = FLOWER_GREEN_ANI_ATTACK_BOTTOM_RIGHT;
					else
						ani = FLOWER_GREEN_ANI_MOVE_BOTTOM_RIGHT;
				}

			}
			else if (nx == -1)
			{
				if (ny == 1)
				{
					if (isAttack)
						ani = FLOWER_GREEN_ANI_ATTACK_UPPER_LEFT;
					else
						ani = FLOWER_GREEN_ANI_MOVE_UPPER_LEFT;
				}
				else
				{
					if (isAttack)
						ani = FLOWER_GREEN_ANI_ATTACK_BOTTOM_LEFT;
					else
						ani = FLOWER_GREEN_ANI_MOVE_BOTTOM_LEFT;
				}
			}
		}
		else
			if (typeColor == FLOWER_TYPE_GREEN_BITE)
			{
				ani = FLOWER_GREEN_BITE_ANI_MOVE_ATTACK;
			}
	//DebugOut(L"ani :\n %d", ani);
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CFlower::CreateFireBall(vector<LPGAMEOBJECT>* listFireBall)
{
	if (isCreateFireBall)
	{
		CFireBall* fireball = new CFireBall();
		fireball->SetPosition(x, y);
		if (nx == 1)
		{
			if (player->y < y)
				fireball->SetState(FIREBALL_STATE_FLY_UPPER_RIGHT);
			else
				fireball->SetState(FIREBALL_STATE_FLY_BOTTOM_RIGHT);
		}
		else
		{
			if (player->y < y)
				fireball->SetState(FIREBALL_STATE_FLY_UPPER_LEFT);
			else
				fireball->SetState(FIREBALL_STATE_FLY_BOTTOM_LEFT);
		}
		listFireBall->push_back(fireball);
		isCreateFireBall = false;
	}
}
