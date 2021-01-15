#include "Switch_P.h"
#include "ExplosiveEffect.h"
#include "WeakBrick.h"

CSwitch_P::CSwitch_P(float x, float y)
{
	this->type = TYPE::SWITCH_P;
	SetPosition(x, y);
	this->SetState(SWITCH_P_STATE_NORMAL);
}

void CSwitch_P::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_P_STATE_NORMAL:
		break;
	case SWITCH_P_STATE_PRESSED:
		break;
	}
}


//void CSwitch_P::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//}

void CSwitch_P::Render()
{
	if (state == SWITCH_P_STATE_PRESSED)
		ani = ITEM_SWITCH_P_ANI_PRESSED;
	else
		ani = ITEM_SWITCH_P_ANI_NORMAL;
	animation_set->at(ani)->Render(x, y);
}

void CSwitch_P::TranFormationBrick(vector<LPGAMEOBJECT>* listBrick, vector<LPGAMEOBJECT> *listItem)
{
	for (size_t i = 0; i < listBrick->size(); i++)
	{
		if (listBrick->at(i)->type == TYPE::WEAK_BRICK)
		{
			CWeakBrick* weakBrick = dynamic_cast<CWeakBrick*>(listBrick->at(i));
			weakBrick->TranFormation(listItem);
		}
	}
}

void CSwitch_P::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SWITCH_P_STATE_PRESSED)
		return;
	left = x;
	top = y;
	right = left + SWITCH_P_BBBOX_WIDTH;
	bottom = top + SWITCH_P_BBBOX_HEIGHT;
}
