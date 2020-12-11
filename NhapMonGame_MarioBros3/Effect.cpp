#include "Effect.h"

CEffect::CEffect()
{
	category = CATEGORY::EFFECT;                                   
	isActive = true;
	if (timestartEffect == TIME_DEFAULT)
		timestartEffect = GetTickCount();
	animation_set = CAnimationSets::GetInstance()->Get(8);
}



void CEffect::SetState(int state)
{

}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
