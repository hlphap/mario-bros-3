#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

bool CGameObject::isCollisionWithObj(LPGAMEOBJECT coObj)
{
	if (coObj != NULL)
	{
		float thisLeft, thisTop, thisRight, thisBottom, objLeft, objTop, objRight, objBottom;
		this->GetBoundingBox(thisLeft, thisTop, thisRight, thisBottom);
		coObj->GetBoundingBox(objLeft, objTop, objRight, objBottom);

		if (CGame::GetInstance()->CheckAABB(thisLeft, thisTop, thisRight, thisBottom, objLeft, objTop, objRight, objBottom))
			return true;

		LPCOLLISIONEVENT e = SweptAABBEx(coObj);
		bool check;
		if (e->t > 0 && e->t <= 1.0f)
			check = true;
		else
			check = false;
		return check;
	}
	else
		return false;
}

bool CGameObject::isCheckInCamera()
{
	float cam_x = CGame::GetInstance()->GetCamPosX();
	float cam_y = CGame::GetInstance()->GetCamPosY();
	
	//DebugOut(L"GetScreenWidth %f", CGame::GetInstance()->GetScreenWidth());
	if (this->x + 16 < cam_x )
		return false;
	if (this->x > cam_x + (float)CGame::GetInstance()->GetScreenWidth())
		return false;
	/*if (this->y - 16 < cam_y)
		return false;
	if (this->y > cam_y + (float)CGame::GetInstance()->GetScreenHeight())
		return false;*/
	return true;
}

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

/*
	Extension of original SweptAABB to deal with two moving listMapObj
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable listMapObj

	coObjects: the list of colliable listMapObj
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)right - (int)left;
	rect.bottom = (int)bottom - (int)top;

	//DebugOut(L"Left player bb : %f", left);
	CGame::GetInstance()->Draw(left, top , bbox, rect.left, rect.top, rect.right, rect.bottom, 100);
}

CGameObject::~CGameObject()
{
	
}