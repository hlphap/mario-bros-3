#include "NewGame.h"

CNewGame::CNewGame()
{
	isActive = true;
	this->type = TYPE::NEWGAME;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(26);
	SetAnimationSet(ani_set);
	vy = -0.06f;
}

CNewGame::~CNewGame()
{
}

void CNewGame::Update(DWORD dt, vector<LPGAMEOBJECT>* staticObj)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CNewGame::Render()
{
	animation_set->at(1)->Render(x, y);
}

void CNewGame::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b;
}
