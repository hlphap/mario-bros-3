#pragma once
#include "Effect.h"
#include "Mario.h"

#define EFFECT_ENDSCENCE_DEFAULT -1
class CSelectionEffect :public CEffect
{
public:
	CMario* mario;
	bool location = false; //0 ->1 player // 1 -> 2 player
public:
	CSelectionEffect(CMario *mario, float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj);
	void SetState(int state);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

