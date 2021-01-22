#pragma once
#include "GameObject.h"
class CBackGroundIntro : public CGameObject
{
public:
	CBackGroundIntro();
	~CBackGroundIntro();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* staticObj);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

