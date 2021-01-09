#pragma once
#include "Item.h"
#include "QuestionBrick.h"
#include "ColorBox.h"
#include "Utils.h"

//Speed
#define LEAF_TREE_GROW_UP	 0.2
#define LEAF_TREE_SPEED_FALL	 0.02

//BBox
#define LEAF_TREE_BBOX_WIDTH	16
#define LEAF_TREE_BBOX_HEIGHT	16

//Distance
#define DISTANCE_FROM_QUESTIONBRICK_TO_MAXPOSX	50

//State
#define	LEAF_TREE_STATE_GROW_UP					 100
#define	LEAF_TREE_STATE_FALL					 200	

class CLeafTree : public CItem
{
public:
	float minPosY;
	float minPosX;
	float maxPosX;
	CLeafTree(float x, float y);
	void Update(DWORD dt, vector<CGameObject*>* listMapObj);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};