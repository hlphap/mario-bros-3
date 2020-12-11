#include "Item.h"
#include "ColorBox.h"
#include "Utils.h"
#include "QuestionBrick.h"
CItem::CItem()
{
	isActive = true;
	category = CATEGORY::ITEM;
	animation_set = CAnimationSets::GetInstance()->Get(5);
}

void CItem::Update(DWORD dt, vector<CGameObject*>* listMapObj)
{
}

void CItem::Render()
{
}
void CItem::SetState(int state)
{
}
void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}