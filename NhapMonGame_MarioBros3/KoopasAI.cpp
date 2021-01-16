#include "KoopasAI.h"

CKoopasAI::CKoopasAI()
{
}

void CKoopasAI::Update(DWORD dt, vector<LPGAMEOBJECT>* listMapObj)
{
	


	vy += 0.0005f * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CGameObject::Update(dt, listMapObj);
	coEvents.clear();
	CalcPotentialCollisions(listMapObj, coEvents);
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isFalling = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		x += min_tx * dx + nx * 0.5f;
		y += min_ty * dy + ny * 0.01f;

		if (ny != 0)
		{
			vy = 0;
			isFalling = false;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CKoopasAI::Render()
{
	RenderBoundingBox();
}

void CKoopasAI::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	b = t + 26;
	r = x + 17;
}
