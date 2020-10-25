#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH  16
#define QUESTION_BRICK_BBOX_WIDTH 16

class CQuestionBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};