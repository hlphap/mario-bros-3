#pragma once
#include"HUD.h"


class COneCharacter :public CHUD
{
public:
	int aciiCharacter;
public:
	COneCharacter(int aciiCharacter);
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CText :public CGameObject
{
public:
	string st;
	vector<COneCharacter*> listCharacter;
public:
	CText(float x, float y, string st);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};