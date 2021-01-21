#pragma once
#include "Item.h"
#include "QuestionBrick.h"
#include "ColorBox.h"
#include "Utils.h"

//Speed
#define COIN_SPEED_GROUW		 0.05
#define COIN_SPEED_FALL			 0.02

//BBox
#define COIN_BBOX_WIDTH	16
#define COIN_BBOX_HEIGHT	16

//Distance
#define DISTANCE_FROM_QUESTIONBRICK_TO_MINPOSY	50

//State
#define	LEAF_TREE_STATE_GROW_UP					 100
#define	LEAF_TREE_STATE_FALL					 200	

//Animation
#define ITEM_ANI_COIN_IDLE			0
#define ITEM_ANI_COIN_MOVE_SLOW		1
#define ITEM_ANI_COIN_MOVE_FAST		2

#define TIME_TRANSFORM_FROM_COIN_TO_WEAKBRICK		4500
#define COIN_IDLE_STATIC_TRANFORM_TO_WEAKBRICK		100

#define TIME_DEFAULT	0

class CCoin : public CItem
{
public:
	DWORD timeStartTranForM = TIME_DEFAULT;
public:
	float minPosY;

	CCoin(float x, float y, int type);
	void Update(DWORD dt, vector<CGameObject*>* listMapObj);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};