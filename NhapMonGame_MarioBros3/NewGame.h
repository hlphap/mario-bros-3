#pragma once
#include "GameObject.h"
class CNewGame : public CGameObject
{
public:
	CNewGame();
	~CNewGame();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* staticObj);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

