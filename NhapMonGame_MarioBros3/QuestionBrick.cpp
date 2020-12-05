#include "QuestionBrick.h"
#include "Utils.h"

CQuestionBrick::CQuestionBrick(float startY, int type)
{
	this->typeQuestion = type;
	this->start_y = startY;
	SetState(QUESTION_STATE_IDLE);
	
}

void CQuestionBrick::Render()
{
	if (isItem)
		ani = QUESTION_BRICK_ANI_ITEM;
	else
		ani = QUESTION_BRICK_ANI_UNITEM;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BRICK_BBOX_WIDTH * amountX;
	b = y + QUESTION_BRICK_BBOX_WIDTH * amountY;
}


void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* ListItem)
{
	CGameObject::Update(dt, ListItem);
	y += dy;
	if (start_y - y > 10) // Nayr
		vy = -vy;
	//Khi ve trang thai dung yen tao item
	if (y > start_y)
	{
		//Kiem tra type
		switch (typeItem)
		{
		case ITEM_LEVEL_MUSHROOM:
			item = new CMushroom(x,y);
			break;
		case ITEM_LEVEL_TREE_LEAF:
			item = new CLeafTree(x, y);
			break;
		case ITEM_LEVEL_COIN:
			item = new CCoin(x, y,COIN_TYPE_EFFECT);
			break;
		}
		y = start_y;
		ListItem->push_back(item);
		DebugOut(L"Phap");
		SetState(QUESTION_STATE_IDLE);
	}
#pragma region Collison with Coin
	if (isCollisionWithObj(item))
	{
		if (item->isComplete)
			item->isActive = false;
	}
	
#pragma endregion

}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QUESTION_STATE_IDLE:
		{
			vy = 0;
			break;
		}
		case QUESTION_STATE_MOVE_UP:
		{
			vy = -0.05;
			isItem = false;
			break;
		}
	}
}
