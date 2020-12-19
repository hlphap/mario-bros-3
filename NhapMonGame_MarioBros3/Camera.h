#pragma once
#include "Mario.h"
#include "Game.h"
#include "TileMap.h"
class Camera
{
public:
	float cam_x;
	float cam_y;
	bool isInHideMap = false;
	CMario* player;
public:
	Camera(CMario* m);
	void Update();
	void SetCamPos(float x, float y) { this->cam_x = x; this->cam_y = y; }
	float GetCamPosX() { return cam_x; }
	float GetCamPosY() { return cam_y; }
	void SetCamPosY(float cam_y) { this->cam_y = cam_y;}
};

