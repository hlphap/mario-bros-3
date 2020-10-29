#include "QuestionBrick.h"

CQuestionBrick::CQuestionBrick()
{
}

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

//void CQuestionBrick::SetState(int state)
//{
//	/*CGameObject::SetState(state);
//	switch (state)
//	{
//	case QUESTION_STATE_IDLE:
//	{
//		vx = 0;
//		vy = 0;
//		break;
//	}
//	case QUESTION_STATE_MOVE_UP:
//	{
//		vx = 0;
//		vy = 0;
//	}
//	}*/
//}
