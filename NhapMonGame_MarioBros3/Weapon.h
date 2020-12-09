#pragma once
#include "GameObject.h"
#define TIME_DEFAULT 0

class CWeapon : public CGameObject
{
public:
	DWORD timeStartAttack = TIME_DEFAULT;
	bool canKill;
public:
	CWeapon();
	~CWeapon();
};