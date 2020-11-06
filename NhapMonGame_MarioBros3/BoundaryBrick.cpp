#include "BoundaryBrick.h"

void CBoundaryBrick::Render()
{
	//RenderBoundingBox();
}

void CBoundaryBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOUNDARYBRICK_BBOX_WEIGHT * amountX;
	b = y + BOUNDARYBRICK_BBOX_HEIGHT * amountY;
}
