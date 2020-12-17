#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Mushroom.h"
#include "LeafTree.h"
#include "Coin.h"
#include "QuestionBrick.h"

#define QUESTION_BRICK_BBOX_WIDTH  16
#define QUESTION_BRICK_BBOX_HEIGHT 16


#define QUESTION_TYPE_COIN					0
#define QUESTION_TYPE_SPECIAL				1
#define QUESTION_SPEED_UP 0.0002
#define QUESTION_STATE_IDLE	100
#define QUESTION_STATE_MOVE_UP	101

#define QUESTION_BRICK_ANI_ITEM				0
#define QUESTION_BRICK_ANI_UNITEM			1


class CQuestionBrick : public CGameObject
{
public:
	CItem* item;
	float start_y;
	bool isItem = true;
	bool isCollision = false;
	int typeQuestion = QUESTION_TYPE_COIN;
	int typeItem = ITEM_LEVEL_COIN;
public:
	CQuestionBrick(float startY, int type);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};