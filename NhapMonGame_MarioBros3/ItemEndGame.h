#pragma once
#include "Item.h"
#include "QuestionBrick.h"
#include "ColorBox.h"
#include "Utils.h"

#define ITEM_ENDSCENCE_STATE_NORMAL	100
#define ITEM_ENDGAME_STATE_USED	200

class CItemEndScence : public CItem
{
public:
	float posTextX;
	float posTextY;
public:
	CItemEndScence(float x, float y);
	void Update(DWORD dt, vector<CGameObject*>* listMapObj);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};