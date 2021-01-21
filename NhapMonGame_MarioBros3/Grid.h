#pragma once
#include "Mario.h"
#include "Camera.h"
#include "Brick.h"
#include "ColorBox.h"
#include "CloudBrick.h"
#include "WeakBrick.h"
#include "QuestionBrick.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Flower.h"
#include "Koopas.h"
#include "ItemEndGame.h"
#include "MovingWood.h"
#include "BomerangBrother.h"

#define OBJECT_TYPE_MARIO			0
#define OBJECT_TYPE_BRICK			1
#define OBJECT_TYPE_GOOMBA			2
#define OBJECT_TYPE_KOOPAS			3
#define OBJECT_TYPE_FLOWER			4
#define OBJECT_TYPE_GROUND			5
#define OBJECT_TYPE_COLORBOX		6
#define OBJECT_TYPE_PIPE			7
#define OBJECT_TYPE_QUESTIONBRICK	8
#define OBJECT_TYPE_WEAK_BRICK		9
#define OBJECT_TYPE_CLOUD_BRICK		10
#define OBJECT_TYPE_COIN_SPIN		11
#define OBJECT_TYPE_BULLET			12
#define OBJECT_TYPE_TREE			13
#define	OBJECT_TYPE_ITEM_ENDSCENCE	14
#define	OBJECT_TYPE_MOVING_WOOD		15
#define OBJECT_TYPE_BOMERANGBROTHER	16
#define OBJECT_TYPE_SELECT_EFFECT	17
#define OBJECT_TYPE_BOUNDARYBRICK	9999
class Grid
{
public:
	CMario* mario;
	int cellWidth;
	int cellHeight;
	vector<LPGAMEOBJECT> listEnemy_S;
	vector<LPGAMEOBJECT> listItems_S;
	int mapW;
	int mapH;

	int numRow;
	int numCol;

	Camera* cam;
	vector<vector<vector<LPGAMEOBJECT>>> unMoveObj;
	vector<vector<vector<LPGAMEOBJECT>>> moveObj;
public:
	void GridResize();
	void InsertObjToGrid(string line);
	CGameObject* CreateNewObj(string line);
	void PushObjToGrid(CGameObject* obj);
	void UpdateGrid();
	Grid(Camera *cam);
	~Grid() {};
	void GetListObj(vector<LPGAMEOBJECT>& listObj, vector<LPGAMEOBJECT>& listEnemy, vector<LPGAMEOBJECT> &);
	void ClearGrid();
};

