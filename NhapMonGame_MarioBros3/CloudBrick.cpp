#include "CloudBrick.h"

CCloudBrick::CCloudBrick()
{
	isActive = true;
	category = CATEGORY::GROUND;

}

void CCloudBrick::Render()
{
	
}

void CCloudBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * amountX;
	b = y + BRICK_BBOX_HEIGHT * amountY;
}