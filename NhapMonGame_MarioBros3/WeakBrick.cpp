#include "WeakBrick.h"
#include "Coin.h"

CWeakBrick::CWeakBrick(float x, float y, int type)
{
	this->typeWeakBrick = type;//Brick is three type, 0 non_Item, 1 mushroom, 2 P_Switch
	this->isActive = true;
	this->category = CATEGORY::GROUND;
	this->type = TYPE::WEAK_BRICK;
	this->start_y = y;
	this->SetPosition(x, y);
	animation_set = CAnimationSets::GetInstance()->Get(22);
	SetState(WEAKBRICK_STATE_IDLE);

}

void CWeakBrick::Deployed_WeakBrick(vector<LPGAMEOBJECT>* listEffect)
{
	CPieceBrickEffect* topLeftPiece = new CPieceBrickEffect(x - 1, y - 2, -1, 2);
	CPieceBrickEffect* topRightPiece = new CPieceBrickEffect(x + 16 - BROKEN_BRICK_PIECE_WIDTH + 1, y - 2, 1, 2);
	CPieceBrickEffect* bottomLeftPiece = new CPieceBrickEffect(x - 1, y + 16 - BROKEN_BRICK_PIECE_HEIGHT, -1, 1);
	CPieceBrickEffect* bottomRightPiece = new CPieceBrickEffect(x + 16 - BROKEN_BRICK_PIECE_WIDTH + 1, y + 16 - BROKEN_BRICK_PIECE_HEIGHT, 1, 1);
	listEffect->push_back(topLeftPiece);
	listEffect->push_back(topRightPiece);
	listEffect->push_back(bottomLeftPiece);
	listEffect->push_back(bottomRightPiece);
	isActive = false;
}

void CWeakBrick::TranFormation(vector<LPGAMEOBJECT>* listItem)
{
	if (typeWeakBrick == WEAKBRICK_TYPE_NON_ITEM)
	{
		CCoin* coin = new CCoin(x, y, TYPE::COIN_IDLE_STATIC);
		coin->timeStartTranForM = GetTickCount();
		listItem->push_back(coin); // Tranform from WeakBrick to Coin
		isActive = false;
	}
}

void CWeakBrick::Render()
{
	if (isItem)
		ani = 0;
	else
		ani = 1;
	animation_set->at(ani)->Render(x, y);
}

void CWeakBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * 1;
	b = y + BRICK_BBOX_HEIGHT * 1;
}

void CWeakBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WEAKBRICK_STATE_IDLE:
		vy = 0;
		break;
	case WEAKBRICK_STATE_MOVE_UP:
	{
		vy = -0.08f;
		isItem = false;
		if (typeWeakBrick == WEAKBRICK_TYPE_ITEM_COIN_EFFECT)
		{
			if (numCoinEffect < 4)
			{
				isItem = true;
			}
		}
		break;
	}
	}
}


void CWeakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* listItems)
{
	CGameObject::Update(dt, listItems);
	y += dy;
	if (start_y - y > 10) // Nayr
		vy = fabs(vy);
	if (y > start_y)
	{
		switch(typeWeakBrick)
		{
		case WEAKBRICK_TYPE_ITEM_MUSHROOM:
			item = new CMushroom(x, y, MUSHROOM_GREEN); //1 la green
			break;
		case WEAKBRICK_TYPE_ITEM_P_SWITCH:
			item = new CSwitch_P(x, y - 16);
			break;
		case WEAKBRICK_TYPE_ITEM_COIN_EFFECT:
		{
			item = new CCoin(x, y, TYPE::COIN_EFFECT);
			numCoinEffect++;
			break;
		}
		case WEAKBRICK_TYPE_ITEM_TREE_LEAF:
			item = new CLeafTree(x, y - 16);
			break;
		}
		y = start_y;
		isComplete = true;
		if (item!=NULL)
			listItems->push_back(item);
		SetState(WEAKBRICK_STATE_IDLE);
	}

	
}



