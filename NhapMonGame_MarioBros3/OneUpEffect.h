#pragma once
#include "Effect.h"

#define TIME_EXITS_EFFECT  1000
#define EFFECT_ANI_ONE_UP  11
class COneUpEffect : public CEffect
{
public:
public:
	COneUpEffect(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

