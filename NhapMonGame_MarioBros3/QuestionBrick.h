#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH  16
#define QUESTION_BRICK_BBOX_WIDTH 16

#define QUESTION_SPEED_UP 0.0002
#define QUESTION_STATE_IDLE	100
#define QUESTION_STATE_MOVE_UP	101

class CQuestionBrick : public CGameObject
{
public:
	CQuestionBrick();
	//const float start_x = x;
	//const float start_y = y;
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//void SetState(int state);
	//	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};