#pragma once
#include "Mario.h"
#include "Camera.h"
class Grid
{
	CMario* mario;
	int cellWidth, celHeight;
	vector<LPGAMEOBJECT> listEnemy_InCam;
	vector<LPGAMEOBJECT> listEnemy_OutCam;
	vector<LPGAMEOBJECT> listMapObj;
	vector<LPGAMEOBJECT> listItem;
public:
	void PushBackGrid(LPGAMEOBJECT obj, bool Check = false);
	Grid();
	~Grid();
	void Update(DWORD dt, Camera* cam);
	void Render();
	void ClearGrid();
};

