#include "Number3.h"

CNumber3::CNumber3()
{
	isActive = true;
	this->type = TYPE::NUMBER3;
}

CNumber3::~CNumber3()
{
}

void CNumber3::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CNumber3::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b;
}
