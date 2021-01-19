#include "Bomerang.h"
#include "Utils.h"




CBomerang::CBomerang(int nx, float x, float y)
{

		isActive = true;
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(26));
		SetPosition(x, y);
		minX = x;
		maxX = x + 100;
		minY = y;
		maxY = y + 10;
		SetState(BOOMERANG_STATE_MOVING_ATTACK);

}

void CBomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nvx: %f", vx);
	if (state != BOOMERANG_STATE_MOVING_RETURN)
		vy += 0.00006f * dt;
	if (x > maxX)
	{
		SetState(BOOMERANG_STATE_DOWN_ATTACK);
	}
	if (y > maxY)
	{
		SetState(BOOMERANG_STATE_MOVING_RETURN);
	}

	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void CBomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOMERANG_BBOX_WIDTH;
	b = y + BOMERANG_BBOX_HEIGHT;
}

void CBomerang::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CBomerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch(state)
	{
	case BOOMERANG_STATE_MOVING_ATTACK:
		vx = 0.12f;
		vy = -0.05f;
		break;
	case BOOMERANG_STATE_DOWN_ATTACK:
		vx = 0.08f;
		vy = 0.1f;
		break;
	case BOOMERANG_STATE_MOVING_RETURN:
		vy = 0;
		vx = -0.1;
		break;
	}
}
