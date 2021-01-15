#pragma once
#include "Mario.h"
#include "Game.h"
#include "TileMap.h"

#define CAMERA_SPEED_X	 0.03f
class Camera
{
public:
	float cam_x= 0;
	float cam_y= 0;

	float vx;
	bool isInHideMap = false;
	CMario* player;
	TileMap* map;
	int typeCamera;
	//Flag
public:
	Camera(CMario* m, TileMap *map, int typeCamera);
	void Update(DWORD dt);
	void SetCamPos(float x, float y) { this->cam_x = x; this->cam_y = y; }
	float GetCamPosX() { return cam_x; }
	float GetCamPosY() { return cam_y; }
	void SetCamPosY(float cam_y) { this->cam_y = cam_y;}
};

