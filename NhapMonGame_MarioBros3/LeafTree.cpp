#include "LeafTree.h"

CLeafTree::CLeafTree(float x, float y)
{
	type = TYPE::LEAF_TREE;
	isActive = true;
	SetPosition(x, y);
	minPosY = y - QUESTION_BRICK_BBOX_HEIGHT - 16; // Vi tri cao nhat co the
	minPosX = x;
	maxPosX = x + DISTANCE_FROM_QUESTIONBRICK_TO_MAXPOSX; //min,maxPos bien do dao dong theo phuong X
	nx = 1;
	SetState(LEAF_TREE_STATE_GROW_UP); //Cho Item phat trien ra khoi QuesionBrick
}

void CLeafTree::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
	vector<LPCOLLISIONEVENT> coObjEvents;
	vector<LPCOLLISIONEVENT> coObjEventsResult;
	coObjEvents.clear();
	if (!isComplete)
	{
		if (y < minPosY)
		{
			isComplete = true;
			vy = 0;
		}
	}

	CGameObject::Update(dt, listMapObj);

	if (isComplete)
	{
		SetState(LEAF_TREE_STATE_FALL);
	}
	x += dx;
	y += dy;
}

void CLeafTree::Render()
{
	if (nx == 1)
		ani = ITEM_ANI_TREE_LEAF_RIGHT;
	else
		ani = ITEM_ANI_TREE_LEAF_LEFT;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CLeafTree::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_TREE_STATE_GROW_UP:
		vy = -LEAF_TREE_GROW_UP;
		break;
	case LEAF_TREE_STATE_FALL:
		if (x <= minPosX)
		{
			vx = 0.06;
			nx = 1;
		}
		if (x >= maxPosX)
		{
			vx = -0.06;
			nx = -1;
		}
		vy = LEAF_TREE_SPEED_FALL;
		break;

	}
}

void CLeafTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LEAF_TREE_BBOX_WIDTH;
	b = y + LEAF_TREE_BBOX_HEIGHT;
}
