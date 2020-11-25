#pragma once
#include "GameObject.h"
#define TIME_DEFAULT 0

class CWeapon : public CGameObject
{
public:
	DWORD timeStartAttack = TIME_DEFAULT;
	bool canKill;
	int numDame;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	CWeapon();
	~CWeapon();
};