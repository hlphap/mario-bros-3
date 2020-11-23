#pragma once
#include "GameObject.h"
#include "MarioGeneral.h"
#include "Bullet.h"
#include "Tail.h"

#define MARIO_WALKING_DECELERATION						0.00015f
#define MARIO_WALKING_ACCELERATION						0.00015f
#define MARIO_WALKING_MAX_SPEED							0.08f

#define MARIO_RUNNING_DECELERATION						0.000325f
#define MARIO_RUNNING_ACCELERATION						0.00003f
#define MARIO_RUNNING_MAX_SPEED							0.15f

#define MARIO_SPEED_CAN_STOP							0.04
#define MARIO_BOUNCE									15

#define FRICTION										0.0016875f
#define MARIO_JUMP_SPEED_Y								0.255f
#define MARIO_JUMP_MAX_SPEED_Y							0.00015f
#define MARIO_JUMP_DEFLECT_SPEED						0.2f
#define MARIO_GRAVITY									0.00045f
#define MARIO_DIE_DEFLECT_SPEED							0.5f
#define TIME_DEFAUL										0
#define MARIO_CAN_FLY_TIME								4500

class CMario : public CGameObject
{
public:
	CMarioGeneral* mario_general;
	CGameObject *bringKoopas = NULL;
	CWeapon* weapon;
	int level;

	int untouchable;
	float start_x;	
	float start_y;

	//Timer
	DWORD untouchable_start;
	DWORD timeAllowFly;
	DWORD timeStartFly = TIME_DEFAUL;
	DWORD timeStartAttack = TIME_DEFAUL;
	DWORD timeStartKick = TIME_DEFAUL;
	


	
	//Flag
	bool isWalking = false;
	bool isOnAir = false;
	bool isSitting = false;
	bool isSpeedUping = false;
	bool isSpeedUp = false;
	bool isSpeedMax = false;
	bool isBlockFall = false;
	bool isStop = false;
	bool isFalling = false;
	bool isKeepJump_SlowFalling = false;
	bool isKeepJump_HightFlying = false;
	bool isAttacking = false;
	bool isKeepJump = false;
	bool isKicking = false;
	bool isHoldShell = false;
	bool isHoldingShell = false;
	byte numFall = 0;
	int ani = -1;

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

	//Control player
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
	void Kick();
	void SpeedUp();
	void HoldShell();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};