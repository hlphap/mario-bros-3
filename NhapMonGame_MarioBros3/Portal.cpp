#include "Portal.h"


CPortal::CPortal(bool isLeft, bool isRight, bool isUp, bool isDown, int scene_id)
{
	isActive = true;
	this->type = TYPEPITSTOP::PORTAL;
	this->scene_id = scene_id;
	this->isAllowLeft = isLeft;
	this->isAllowRight = isRight;
	this->isAllowUp = isUp;
	this->isAllowDown = isDown;

}



void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + amountX * 16;
	b = y + amountY * 16;
}