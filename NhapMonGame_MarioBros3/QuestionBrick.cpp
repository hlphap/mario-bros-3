#include "QuestionBrick.h"
#include "Utils.h"

CQuestionBrick::CQuestionBrick(float startY, int type)
{
	category = CATEGORY::GROUND;
	this->type = TYPE::QUESTION_BRICK;
	isActive = true;
	this->typeQuestion = type; // 0 -> coin , 1 special
	this->start_y = startY;
	SetState(QUESTION_STATE_IDLE);
	animation_set = CAnimationSets::GetInstance()->Get(21);

}

void CQuestionBrick::Render()
{
	if (isItem)
		ani = QUESTION_BRICK_ANI_ITEM;
	else
		ani = QUESTION_BRICK_ANI_UNITEM;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BRICK_BBOX_WIDTH;
	b = y + QUESTION_BRICK_BBOX_WIDTH;
}


void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* listItem)
{
	CGameObject::Update(dt, listItem);
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
			item = new CMushroom(x, y, MUSHROOM_RED); //0 la red
			break;
		case ITEM_LEVEL_TREE_LEAF:
			item = new CLeafTree(x, y);
			break;
		case ITEM_LEVEL_COIN:
			item = new CCoin(x, y, TYPE::COIN_EFFECT);
			break;
		}	
		listItem->push_back(item);
		y = start_y;
		SetState(QUESTION_STATE_IDLE);
	}
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
			vy = -0.08;
			isItem = false;
			break;
		}
	}
}
