#include "PieceBrickEffect.h"

CPieceBrickEffect::CPieceBrickEffect(float x, float y, int nx, int deflection)
{
	SetPosition(x, y);
	vx = nx * PIECEBRICK_SPEED_DEFLECT_X;
	vy = deflection * PIECEBRICK_SPEED_DEFLECT_Y;
}

void CPieceBrickEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += PIECE_BRICK_GRAVITY * dt;
	
	x += dx;
	y += dy;
}

void CPieceBrickEffect::Render()
{
	animation_set->at(10)->Render(x, y);
}

void CPieceBrickEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BROKEN_BRICK_PIECE_WIDTH;
	b = t + BROKEN_BRICK_PIECE_HEIGHT;
}
