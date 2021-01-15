#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
public:
	int scene_id;	// target scene to switch to 
	bool isAllowLeft = false;
	bool isAllowRight = false;
	bool isAllowUp = false;
	bool isAllowDown = false;

public:
	CPortal(bool isLeft, bool isRight, bool isUp, bool isDown, int scene_id);
	CPortal(int scence_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};