#pragma once
#include "HUD.h"
class C1Energy:public CHUD
{
public:
	float energy;

public:
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};


class CEnergy : public CGameObject
{
public:
	unsigned int numEnergy;
	vector<LPGAMEOBJECT> listEnergy;
public:
	CEnergy(int numEnergy);
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};
