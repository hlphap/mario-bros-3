#pragma once
#include "Item.h"
#include "QuestionBrick.h"
#include "ColorBox.h"
#include "Utils.h"

#define MUSHROOM_SPEED_GROWN_UP 0.05;
#define	MUSHROOM_STATE_GROWN_UP 100

class CMushroom: public CItem
{
public:
	float minPosY;
	CMushroom(float x, float y);
	void Update(DWORD dt, vector<CGameObject*>* listMapObj);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};