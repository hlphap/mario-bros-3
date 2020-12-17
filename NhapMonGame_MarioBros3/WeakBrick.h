#pragma once
#include "GameObject.h"
#include "PieceBrickEffect.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define WEAKBRICK_TYPE_NON_ITEM			0
#define WEAKBRICK_TYPE_ITEM_MUSHROOM	1
#define WEAKBRICK_TYPE_ITEM_P_SWITCH	2

//STATE
#define WEAKBRICK_STATE_DEPLOYED		100
#define WEAKBRICK_STATE_TRANFORMATION	200

class CWeakBrick : public CGameObject
{
public:
	int typeWeakBrick = WEAKBRICK_TYPE_NON_ITEM;
public:
	CWeakBrick(int type);
	void Deployed_WeakBrick(vector<LPGAMEOBJECT>* listEffect);
	void TranFormation(vector<LPGAMEOBJECT>* listItem);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};