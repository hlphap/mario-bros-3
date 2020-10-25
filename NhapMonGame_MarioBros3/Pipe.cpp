#include "Pipe.h"
void CPipe::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * amountX;
	b = y + BRICK_BBOX_HEIGHT * amountY;
}