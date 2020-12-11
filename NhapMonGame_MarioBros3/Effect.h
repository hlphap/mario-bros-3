#pragma once
#include "GameObject.h"

#define TIME_DEFAULT  0

#define EFFECT_ANI_BULLET_EXPLOSIVE	9
class CEffect :public CGameObject
{
public:
	DWORD timestartEffect = TIME_DEFAULT;
public:
	CEffect();
	virtual void Render() = 0;
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};