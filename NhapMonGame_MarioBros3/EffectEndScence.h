#pragma once
#include "Effect.h"

#define EFFECT_ENDSCENCE_DEFAULT -1
class CEffectEndScence :public CEffect
{
public:
	int typeEffect = EFFECT_ENDSCENCE_DEFAULT;
public:
	CEffectEndScence(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj);
	void SetState(int state);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float&b);
};

