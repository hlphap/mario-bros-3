#include "WeakBrick.h"
#include "Coin.h"

CWeakBrick::CWeakBrick(int type)
{
	this->typeWeakBrick = type;//Brick is three type, 0 non_Item, 1 mushroom, 2 P_Switch
	this->isActive = true;
	this->category = CATEGORY::BRICK;
	this->type = TYPE::WEAK_BRICK;
	animation_set = CAnimationSets::GetInstance()->Get(22);
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
	CCoin* coin = new CCoin(x, y, TYPE::COIN_IDLE_STATIC);
	coin->timeStartTranForM = GetTickCount();
	listItem->push_back(coin); // Tranform from WeakBrick to Coin
	isActive = false;
}

void CWeakBrick::Render()
{
	animation_set->at(0)->Render(x, y);
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
}


void CWeakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
}



