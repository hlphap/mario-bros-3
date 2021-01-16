#pragma once
#include "Mario.h"
#include "Camera.h"

class Grid
{
	CMario* mario;
	int cellWidth;
	int cellHeight;

	int numRow;
	int numCol;

	TileMap* map;
	Camera* cam;
	vector<vector<vector<LPGAMEOBJECT>>> cell;
public:
	void UpdateGrid(vector<LPGAMEOBJECT> listObj, vector<LPGAMEOBJECT>listEnemy);
	Grid(TileMap *map, Camera *cam);
	~Grid() {};
	void GetListObj(vector<LPGAMEOBJECT>& listObj, vector<LPGAMEOBJECT>& listEnemy);
	void ClearGrid();
};

