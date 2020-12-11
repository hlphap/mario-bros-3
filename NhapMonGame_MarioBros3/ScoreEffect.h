#pragma once
#include "Effect.h"
#define	EFFECT_ANI_POINT_100				0
#define	EFFECT_ANI_POINT_200				1
#define	EFFECT_ANI_POINT_400				2
#define	EFFECT_ANI_POINT_800				3
#define	EFFECT_ANI_POINT_1000				4
#define	EFFECT_ANI_POINT_2000				5
#define	EFFECT_ANI_POINT_4000				6
#define	EFFECT_ANI_POINT_8000				7

//Time
#define TIME_EXITS_EFFECT  1000
class CScoreEffect : public CEffect
{
public:
	int score = 100;
public:
	CScoreEffect(float x, float y);
	void SetScore(int score) { this->score = score;};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

