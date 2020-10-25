#include "Item.h"

void CItem::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}
void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}