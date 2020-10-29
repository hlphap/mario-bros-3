#pragma once
#include "GameObject.h"
#include "MarioGeneral.h"
#include "Bullet.h"

class CMario : public CGameObject
{
public:
	int level;

	int untouchable;
	DWORD untouchable_start;
	DWORD timeStartFly;

	float start_x;			// initial position of Mario at scene
	float start_y;

	float last_vx;
	
	CMarioGeneral* mario_general;
	CBullet* bullet;
	vector<CBullet*> bullets;

	bool isOnAir = false;
	bool isSitting = false;
	bool isSpeedUping = false;
	bool isSpeedUp = false;
	bool isSpeedMax = false;
	bool isStop = false;
	bool isFalling = false;
	bool isKeepJump_SlowFalling = false;
	bool isKeepJump_HightFlying = false;
	bool isAttacking = false;
	bool isBlockFall = false;
	bool isBlockKeepJump = true;


public:
	CMario(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	int RenderFromAniGroup();

	void DecreaseSpeed(float speedDown);
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	int GetLevel() { return level; };
	float Getvx() { return vx; }
	bool GetSpeeUp() { return isSpeedUp; }
	bool GetJump() { return isOnAir; }
	void Reset();

	//Control mario
	void Go();
	void Left();
	void Right();
	void Jump();
	void Sit();
	void Idle();
	void Stop();
	void Fall();
	void Attack();
	void KeepJump();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};