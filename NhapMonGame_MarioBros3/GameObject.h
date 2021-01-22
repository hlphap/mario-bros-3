#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "define.h"
#include "Sprites.h"
#include "Animations.h"
#include "Game.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	bool isActive;
	int category;
	int type;

	float x;
	float y;

	float amountX;
	float amountY;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float backup_vx;
	float backup_vy;

	int nx;
	int ny;

	int state;
	int ani = -1;

	bool inGrid;
	//Grid
	int GridL, GridR, GridT, GridB;
	int w, h;

	DWORD dt;

	LPANIMATION_SET animation_set;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y;}
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	
	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	bool isCollisionWithObj(LPGAMEOBJECT obj);
	bool isCheckInCamera();
	void SetGridPos(int GL, int GT, int GR, int GB)
	{
		GridL = GL;
		GridT = GT;
		GridR = GR;
		GridB = GB;
	}
	void GetGridPos(int& GL, int& GT, int& GR, int& GB)
	{
		GL = GridL;
		GT = GridT;
		GR = GridR;
		GB = GridB;
	}
	void CreatePosGrid(float l, float t, float r, float b)
	{
		GridT = int(t / CGame::GetInstance()->cellH);
		GridL = int(l / CGame::GetInstance()->cellW);
		GridR = ceil(r / CGame::GetInstance()->cellW);
		GridB = ceil(b / CGame::GetInstance()->cellH);
	}
	~CGameObject();
};

