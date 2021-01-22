#include "Ground.h"

CGround::CGround()
{
	isActive = true;
	category = CATEGORY::GROUND;
}

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * amountX;
	b = y + BRICK_BBOX_HEIGHT * amountY;
}