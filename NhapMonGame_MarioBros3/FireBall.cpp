#include "FireBall.h"
#include "Pipe.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "CloudBrick.h"
#include "ColorBox.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Utils.h"

CFireBall::CFireBall()
{
	isActive = true;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	animation_set = animation_sets->Get(7);
}

void CFireBall::Render()
{
	int ani = 0;
	if (isExploding)
		ani = 1;
	else
		if (nx == 1)
		{
			ani = 0;
		}
		else
			if (nx == -1)
			{
				ani = 0;
			}
	animation_set->at(ani)->Render(x, y);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_WIDTH;
}
void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_FLY_BOTTOM_LEFT:
	{
		vx = -BULLET_FLY_SPEED_X;
		vy = BULLET_FLY_SPEED_Y;
		break;
	}
	case FIREBALL_STATE_FLY_UPPER_LEFT:
	{
		vx = -BULLET_FLY_SPEED_X;
		vy = -BULLET_FLY_SPEED_Y;
		break;
	}
	case FIREBALL_STATE_FLY_BOTTOM_RIGHT:
	{
		vx = BULLET_FLY_SPEED_X;
		vy = BULLET_FLY_SPEED_Y;
		break;
	}
	case FIREBALL_STATE_FLY_UPPER_RIGHT:
	{
		vx = BULLET_FLY_SPEED_X;
		vy = -BULLET_FLY_SPEED_Y;
		break;
	}
	/*case BULLET_STATE_EXPLOSIVE:
	{
		isExploding = true;
		if (timeStartColl == TIME_DEFAULT) timeStartColl = GetTickCount();
		vx = 0;
		vy = 0;
		break;
	}*/
	}
}
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	

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

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;

	//}
	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
