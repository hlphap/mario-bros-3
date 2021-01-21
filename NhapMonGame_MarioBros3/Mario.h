#pragma once
#include "GameObject.h"
#include "MarioGeneral.h"
#include "Bullet.h"
#include "Tail.h"
#include "Portal.h"

#define MARIO_WALKING_DECELERATION						0.00015f
#define MARIO_WALKING_ACCELERATION						0.00015f
#define MARIO_WALKING_MAX_SPEED							0.08f

#define MARIO_RUNNING_DECELERATION						0.000325f
#define MARIO_RUNNING_ACCELERATION						0.00005f
#define MARIO_RUNNING_MAX_SPEED							0.17f

#define MARIO_SPEED_CAN_STOP							0.04
#define MARIO_BOUNCE									15

#define FRICTION										0.0016875f
#define MARIO_JUMP_SPEED_Y								0.255f
#define MARIO_ELASETIC_SPEED_Y							0.2f
#define MARIO_JUMP_MAX_SPEED_Y							0.00015f
#define MARIO_JUMP_DEFLECT_SPEED						0.2f
#define MARIO_GRAVITY									0.00045f
#define MARIO_DIE_DEFLECT_SPEED							0.5f
#define TIME_DEFAULT										0
#define MARIO_CAN_FLY_TIME								4500

class CMario : public CGameObject
{
public:
	static CMario* __instance;
	CMarioGeneral* mario_general;
	CGameObject *bringKoopas = NULL;
	CTail* tail;
	CBullet* bullet;
	CPortal* portalPre = NULL;
	CPortal* portalReturn = NULL;
	int level;

	//Direct Map
	int directSelectMap;
	int lastIndexStop;
	
	//Score
	int score;
	bool changeScore;
	bool doubleScore;

	//
	int numCoin;


	bool isUnTouchable;
	float start_x;	
	float start_y;

	//GoHideMap
	float posY_of_PipeIn;
	float posY_of_PipeOut;
	
	//Timer
	DWORD untouchable_start;
	DWORD timeAllowFly;
	DWORD timeStartFly = TIME_DEFAULT;
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeStartKick = TIME_DEFAULT;
	
	//Flag Go
	bool onPitStop;
	bool isAllowLeft;
	bool isAllowRight;
	bool isAllowUp;
	bool isAllowDown;
	
	//Flag Scence
	bool isGoEndScene;
	bool isSelectMap;
	bool isGoingSelectMap;
	bool isCompleteScene;
	bool isIntroScene = true;
	bool isLocationSelect = false;

	//Flag ...
	bool isDecreaseSpeed;
	bool isSlideOutPipe;
	bool isInMainMap;
	bool isWalking;
	bool isOnAir;
	bool isSitting;
	bool isSpeedUping;
	bool isSpeedUp;
	bool isSpeedMax;
	bool isBlockFall;
	bool isStop;
	bool isFalling;
	bool isKeepJump_SlowFalling;
	bool isKeepJump_HightFlying;
	bool isAttacking;
	bool isKeepJump;
	bool isKicking;
	bool isKeepHoldShell;
	bool isHoldingShell;

	//Flag HideMap
	bool isGoHidenMap ;
	bool isOnPipeGoHideMap;
	bool isPressKeyDown;

	byte numFall;

public:
	CMario(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObj, vector<LPGAMEOBJECT> *coEnemy, vector<LPGAMEOBJECT> *coItem, vector<LPGAMEOBJECT> *coItemIdle, vector<LPGAMEOBJECT>* listEffect, vector<LPGAMEOBJECT> *listPortal, vector<LPGAMEOBJECT> * listFireBall);
	void Render();
	int RenderFromAniGroup();

	
	void CreateEffectCoin(vector<LPGAMEOBJECT> *listEffect);
	void DecreaseSpeed(float speedDown);
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { isUnTouchable = true; untouchable_start = GetTickCount(); }
	void ChangeTheLevel(int typeChange);
	int GetLevel() { return level; };
	float Getvx() { return vx; }
	bool GetSpeeUp() { return isSpeedUp; }
	bool GetJump() { return isOnAir; }
	void Reset();
	static CMario* GetInstance();

	//Control player
	void Elastic();
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

	//Go Hiden Map In Scene
	void GoHiddenMap();
	void GoMainMap();

	//Di chuyen chon Map// Ngoai Selection Map
	void GoSelectMap();

	//Auto Go When Collision with Item End Scene
	void GoEndScence();

	//Set On Map
	void SetOnMap(bool isSelectMap);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};