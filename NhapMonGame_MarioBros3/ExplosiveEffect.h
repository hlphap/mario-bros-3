#pragma once
#include "Effect.h"
#define TIME_EXITS_EFFECT  100
class CExplosiveEffect:public CEffect
{
public:
	CExplosiveEffect(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

