#pragma once
#include "GameObject.h"
class CKoopasAI :public CGameObject
{
public:
	bool isFalling = false;
public:
	CKoopasAI();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

