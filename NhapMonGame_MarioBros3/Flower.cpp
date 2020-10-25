#include "Flower.h"

void CFlower::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}
void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FLOWER_BBOX_WIDTH ;
	b = y + FLOWER_BBOX_HEIGHT ;
}