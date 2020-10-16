#pragma once
#include "GameObject.h"
#include "MarioGeneral.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_ACCELERATOR	0.0002f
#define MARIO_RUNNING_ACCELERATOR	0.0004f
#define MARIO_STOP_WHEN_WALKING_ACCELERATOR 0.0003f
#define MARIO_STOP_WHEN_RUNNING_ACCELERATOR 0.0006f
#define MARIO_FLYING_ACCELERATOR	0.05f
#define MARIO_WALKING_MAX 0.15f
#define MARIO_RUNNING_MAX 0.25f	
#define MARIO_FLYING_MAX 0.2f
////0.1f
//#define MARIO_JUMP_SPEED_Y		0.2f
//#define MARIO_JUMP_DEFLECT_SPEED 0.2f
//#define MARIO_GRAVITY			0.002f
//#define MARIO_DIE_DEFLECT_SPEED	 0.5f
//
//#define MARIO_STATE_IDLE			0
//#define MARIO_STATE_WALKING_RIGHT	100
//#define MARIO_STATE_WALKING_LEFT	200
//#define MARIO_STATE_JUMP			300
//#define MARIO_STATE_DIE				400
//#define MARIO_STATE_SPEED_UP		500
//#define MARIO_STATE_SITTING			600
//#define MARIO_STATE_STOP		700
//#define MARIO_STATE_STOP_LEFT		800
//#define MARIO_STATE_STOP_SPEED_UP	900
//
//
//
//
//
//#define MARIO_BIG_BBOX_WIDTH  15
//#define MARIO_BIG_BBOX_HEIGHT 27
//
//#define MARIO_SMALL_BBOX_WIDTH  13
//#define MARIO_SMALL_BBOX_HEIGHT 15
//
//#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;

	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool isJump = false;


public:
	CMario(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	int RenderFromAniGroup(CMarioGeneral *anigroup);

	void DecreaseSpeed();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	int GetLevel() { return level; };
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};