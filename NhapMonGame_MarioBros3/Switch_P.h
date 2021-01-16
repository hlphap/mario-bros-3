#pragma once
#include "Item.h"
#include "ExplosiveEffect.h"

#define SWITCH_P_BBBOX_WIDTH	16
#define SWITCH_P_BBBOX_HEIGHT	16

#define SWITCH_P_STATE_NORMAL	100
#define SWITCH_P_STATE_PRESSED	200



class CSwitch_P :public CItem
{
public:
	CExplosiveEffect* effect;
	bool isTransformed = false;
public:
	CSwitch_P(float x, float y);
	vector<LPGAMEOBJECT> listCoin;
	void SetState(int state);
	void Render();
	void TranFormationBrick(vector<LPGAMEOBJECT>* listBrick, vector<LPGAMEOBJECT> *listItem);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};