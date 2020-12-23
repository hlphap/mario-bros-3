#include "P_MaxSpeed.h"

CP_MaxSpeed::CP_MaxSpeed()
{

}

void CP_MaxSpeed::Update(DWORD dt)
{
}

void CP_MaxSpeed::Render()
{
	animation_set->at(38)->Render(x, y);
}

void CP_MaxSpeed::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

CP_MaxSpeed::~CP_MaxSpeed()
{
}
