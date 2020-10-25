#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprites.h"

/*
Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	float speedRunRatio;
	vector<LPANIMATION_FRAME> frames;
public:
	DWORD timeStartAni;
	DWORD timeAni;
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void SetHightSpeed(float ratio) { speedRunRatio = ratio; }
	void Render(float x, float y, int alpha = 255);

	void SetCurrentFrame()
	{
		currentFrame = -1;
	}
	void StartAni()
	{
		timeStartAni = GetTickCount64();
	}
	bool IsRenderOver()
	{
		return (GetTickCount64() - timeStartAni > timeAni);
	}
	
};

typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations* GetInstance();
};

typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets* __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);


	static CAnimationSets* GetInstance();
};