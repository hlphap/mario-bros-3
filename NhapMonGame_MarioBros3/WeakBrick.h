#pragma once
#include "GameObject.h"
#include "PieceBrickEffect.h"
#include "Switch_P.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define WEAKBRICK_TYPE_NON_ITEM			0
#define WEAKBRICK_TYPE_ITEM_MUSHROOM	1
#define WEAKBRICK_TYPE_ITEM_P_SWITCH	2
#define WEAKBRICK_TYPE_ITEM_COIN_EFFECT	3
#define WEAKBRICK_TYPE_ITEM_TREE_LEAF	4

//STATE
#define WEAKBRICK_STATE_IDLE		100
#define WEAKBRICK_STATE_MOVE_UP		200


class CWeakBrick : public CGameObject
{
public:
	int numCoinEffect = 0;
	CItem* item;
	bool isItem = true;
	float start_y;
	bool isComplete = false;
	int typeWeakBrick = WEAKBRICK_TYPE_NON_ITEM;
	bool isTranformToNormal = false;
public:
	CWeakBrick(float x, float y, int type);
	void Deployed_WeakBrick(vector<LPGAMEOBJECT>* listEffect);
	void TranFormation(vector<LPGAMEOBJECT>* listItem);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listItems = NULL);
};