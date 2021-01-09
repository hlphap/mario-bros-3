#pragma once
#include "Enemy.h"
#include "FireBall.h"

#define FLOWER_RED_BBOX_WIDTH  16
#define FLOWER_RED_BBOX_HEIGHT 33

#define FLOWER_GREEN_BBOX_WIDTH		17
#define FLOWER_GREEN_BBOX_HEIGHT	25

#define FLOWER_GREEN_BITE_BBOX_WIDTH		16
#define FLOWER_GREEN_BITE_BBOX_HEIGHT		25


//TYPE
#define FLOWER_TYPE_GREEN									0
#define FLOWER_TYPE_RED										1
#define FLOWER_TYPE_GREEN_BITE								2

#define FLOWER_RED_ANI_MOVE_BOTTOM_RIGHT					0
#define FLOWER_RED_ANI_ATTACK_BOTTOM_RIGHT					1
#define FLOWER_RED_ANI_MOVE_UPPER_RIGHT						2
#define FLOWER_RED_ANI_ATTACK_UPPER_RIGHT					3

#define FLOWER_RED_ANI_MOVE_BOTTOM_LEFT						4
#define FLOWER_RED_ANI_ATTACK_BOTTOM_LEFT					5
#define FLOWER_RED_ANI_MOVE_UPPER_LEFT						6
#define FLOWER_RED_ANI_ATTACK_UPPER_LEFT					7


#define FLOWER_GREEN_ANI_MOVE_BOTTOM_RIGHT					8
#define FLOWER_GREEN_ANI_ATTACK_BOTTOM_RIGHT				9
#define FLOWER_GREEN_ANI_MOVE_UPPER_RIGHT					10
#define FLOWER_GREEN_ANI_ATTACK_UPPER_RIGHT					11

#define FLOWER_GREEN_ANI_MOVE_BOTTOM_LEFT					12
#define FLOWER_GREEN_ANI_ATTACK_BOTTOM_LEFT					13
#define FLOWER_GREEN_ANI_MOVE_UPPER_LEFT					14
#define FLOWER_GREEN_ANI_ATTACK_UPPER_LEFT					15

#define FLOWER_GREEN_BITE_ANI_MOVE_ATTACK					16

#define FLOWER_STATE_MOVE_TO_ATTACK				100
#define FLOWER_STATE_MOVE_TO_RETIRE				200
#define FLOWER_STATE_IDLE						300
#define FLOWER_STATE_ATTACK						400
#define FLOWER_STATE_DIE						500

class CFlower : public CEnemy
{
public:
	int typeColor;
	vector<CFireBall*> list_FireBall;
	float start_y;
	float height;

	bool isSleep = false;
	bool isPause;
	bool isMoveAttack = true;
	bool isAttack = false;
	bool isCreateFireBall = false;
	DWORD timeStartAttack = TIME_DEFAULT;
public:
	CFlower(CMario* m, int type);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void CreateFireBall(vector<LPGAMEOBJECT> *listFireBall);
};

