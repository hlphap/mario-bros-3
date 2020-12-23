#pragma once
#include "HUD.h"
class CP_MaxSpeed:public CHUD
{
public:
	CP_MaxSpeed();
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	~CP_MaxSpeed();
};

