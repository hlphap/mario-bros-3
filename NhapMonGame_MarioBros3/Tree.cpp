#include "Tree.h"

CTree::CTree()
{
	isActive = true;
}

void CTree::Render()
{
	animation_set->at(0)->Render(x,y);
	//RenderBoundingBox();
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
