#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

//State
#define ITEM_STATE_COMPLETE			100
#define ITEM_STATE_GROW_UP			200

#define ITEM_LEVEL_COIN				0
#define ITEM_LEVEL_MUSHROOM			1
#define ITEM_LEVEL_TREE_LEAF		2
#define ITEM_LEVEL_FIRE_FLOWER		3


#define ITEM_ANI_MUSHROOM_RED			3
#define ITEM_ANI_TREE_LEAF_LEFT		4
#define ITEM_ANI_TREE_LEAF_RIGHT	5
#define ITEM_ANI_FIRE_FLOWER		6
#define ITEM_SWITCH_P_ANI_NORMAL		7
#define ITEM_SWITCH_P_ANI_PRESSED		8
#define ITEM_ENDSCENCE_ANI				9
#define ITEM_ANI_MUSHROOM_GREEN				10

#define ITEM_GRAVITY				0.00045f



class CItem : public CGameObject
{
public:
	bool isComplete = false;
	CItem();
	virtual void Update(DWORD dt, vector<CGameObject*>* listMapObj);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};