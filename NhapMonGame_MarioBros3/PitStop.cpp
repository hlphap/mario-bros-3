#include "PitStop.h"



CPitStop::CPitStop(bool isLeft, bool isRight, bool isUp, bool isDown)
{
	this->type = TYPEPITSTOP::PITSTOP;
	isActive = true;
	this->isAllowLeft = isLeft;
	this->isAllowRight = isRight;
	this->isAllowUp = isUp;
	this->isAllowDown = isDown;
}

void CPitStop::Render()
{
	RenderBoundingBox();
}

void CPitStop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}
