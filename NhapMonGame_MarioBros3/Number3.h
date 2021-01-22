#pragma once
#include "GameObject.h"
class CNumber3 : public CGameObject
{
public:
	CNumber3();
	~CNumber3();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

