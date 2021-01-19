#pragma once
#include "HUD.h"
#include "Camera.h"
#include "Number.h"
#include "Energy.h"
#include "P_MaxSpeed.h"

#define TIME_MAX_LIVE 300
#define CLOCK_PER_SEC 1000


class CScoreBoard: public CHUD
{
public:
	CMario* mario;
	float x;
	float y;

	//Energy
	int numEnergy, lastnumEnergy;
	DWORD timeStartDecree = TIME_DEFAULT;
	CEnergy* energy;
	CP_MaxSpeed* pMax;

	//Score
	int totalScore = 0;
	CNumber* numbertotalScore;
	//Num Coin Clear
	int numCoin;
	CNumber* numberCoin;

	//TimeCountDown
	int ncountDown;
	CNumber* countDown;

	int timeMaxLive = TIME_MAX_LIVE;
	int clockPerSec = CLOCK_PER_SEC;
	DWORD timeStartPlay = TIME_DEFAULT;

	
public:
	CScoreBoard(CMario* mario);

	void Update(DWORD dt, Camera* cam);
	void Render();
	void DrawBackGround();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

