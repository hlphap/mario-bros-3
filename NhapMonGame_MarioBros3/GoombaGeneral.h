#pragma once
#include <vector>


//KOOPAS TYPE
#define GOOMBA_TYPE_RED												1
#define GOOMBA_TYPE_YELLOW											0

//KOOPAS LEVEL
#define GOOMBA_LEVEL_HAVE_WING										1
#define GOOMBA_LEVEL_DEFAULT										0

//KOOPAS BBOX
#define GOOMBA_BBOX_WEIGHT											16
#define GOOMBA_BBOX_HEIGHT											15
#define GOOMBA_BBOX_HEIGHT_DIE										9


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ANIINDEX
#define	GOOMBA_ANI_FLYING										0
#define	GOOMBA_ANI_MOVING										1
#define GOOMBA_ANI_HAVE_WING_MOVING								2
#define	GOOMBA_ANI_DIE											3
#define	GOOMBA_ANI_DIE_BY_WEAPON								4


//++++++++++++++++++++++++GOOMMBA RED
//=======================================GOOMBA RED HAVE WING====================
#define GOOMBA_ANI_RED_HAVE_WING_FLYING								4
#define GOOMBA_ANI_RED_HAVE_WING_MOVING								9
//=======================================END GOOMBA RED HAVE WING================

//=======================================GOOMBA RED====================
#define GOOMBA_ANI_RED_MOVING										5
#define GOOMBA_ANI_RED_DIE											6 // Giẫm chết
#define GOOMBA_ANI_RED_DIE_BY_WEAPON								7
//=======================================END GOOMBA RED================

//++++++++++++++++++++++++GOOMMBA YELLOW
//=======================================GOOMBA YELLOW HAVE WING====================
#define GOOMBA_ANI_YELLOW_HAVE_WING_FLYING								0
#define GOOMBA_ANI_YELLOW_HAVE_WING_MOVING								8

//=======================================END GOOMBA YELLOW HAVE WING================

//=======================================GOOMBA YELLOW====================
#define GOOMBA_ANI_YELLOW_MOVING										1
#define GOOMBA_ANI_YELLOW_DIE											2 // Giẫm chết
#define GOOMBA_ANI_YELLOW_DIE_BY_WEAPON									3
//=======================================END GOOMBA YELLOW================



using namespace std;
class CGoombaGeneral
{
	static CGoombaGeneral* __instance;
	int IndexBBox;
public:
	CGoombaGeneral();
	vector<int> listAni_goomba_red;
	vector<int> listAni_goomba_yellow;
	void LoadListAni();
	int GetAni_Goomba(int type, int index);
	void GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int level);
	static CGoombaGeneral* GetInstance();
};