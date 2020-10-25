#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BRICK_BBOX_WIDTH * amountX;
	b = y + QUESTION_BRICK_BBOX_WIDTH * amountY;
}