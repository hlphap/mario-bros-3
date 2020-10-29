#include "Bullet.h"
#include "Pipe.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "CloudBrick.h"
#include "ColorBox.h"

CBullet::CBullet()
{
	vy = BULLET_FLY_SPEED_Y;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	animation_set = animation_sets->Get(7);
}

void CBullet::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH * amountX;
	b = y + BULLET_BBOX_WIDTH * amountY;
}
void CBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_FLY_LEFT:
	{
		vx = -BULLET_FLY_SPEED_X;
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
void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vy += BULLET_GRAVITY;
	if (vy > BULLET_FLY_SPEED_Y) vy = BULLET_FLY_SPEED_Y;
	else
	if (vy < -BULLET_FLY_SPEED_Y) vy = -BULLET_FLY_SPEED_Y;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	if (state != BULLET_STATE_EXPLOSIVE)
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
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		
		//
		// Collision logic with other objects
		//
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
			if (dynamic_cast<CGround*>(e->obj))
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


			if (dynamic_cast<CPipe*>(e->obj))
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
			if (dynamic_cast<CBrick*>(e->obj))
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
			if (dynamic_cast<CQuestionBrick*>(e->obj))
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
			if (dynamic_cast<CCloudBrick*>(e->obj))
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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
