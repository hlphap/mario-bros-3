#pragma once
#include "Effect.h"
#define TIME_EXITS_EFFECT	100
#define EFFECT_ANI_IMPACT_BY_TAIL	8
class CImpactEffect: public CEffect
{
public:
	CImpactEffect(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

