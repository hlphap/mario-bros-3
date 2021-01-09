#pragma once
#include <vector>


//KOOPAS TYPE
#define KOOPAS_TYPE_RED												0
#define KOOPAS_TYPE_GREEN											1

//KOOPAS LEVEL
#define KOOPAS_LEVEL_HAVE_WING										2
#define KOOPAS_LEVEL_DEFAULT										1
#define KOOPAS_LEVEL_SHELL											0
//KOOPAS BBOX
#define KOOPAS_BBOX_WIDTH											16
#define KOOPAS_BBOX_HEIGHT											26
#define KOOPAS_BBOX_HEIGHT_SLEEP									8


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ANIINDEX
#define	KOOPAS_ANI_FLYING_LEFT										0
#define	KOOPAS_ANI_FLYING_RIGHT										1
#define	KOOPAS_ANI_WALKING_LEFT										2
#define	KOOPAS_ANI_WALKING_RIGHT									3
#define KOOPAS_ANI_SHELL_IDLE										4
#define KOOPAS_ANI_SHELL_OVERTURNED_IDLE							5
#define KOOPAS_ANI_SHELL_MOVING										6
#define KOOPAS_ANI_SHELL_OVERTURNED_MOVING							7
#define KOOPAS_ANI_SHELL_HEALTH										8
#define KOOPAS_ANI_SHELL_OVERTURNED_HEALTH							9
#define KOOPAS_ANI_SHELL_REVIAL_KHONGCHAN							10
#define KOOPAS_ANI_SHELL_REVIAL_COCHAN								11
#define KOOPAS_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN				12
#define KOOPAS_ANI_SHELL_OVERTURNED_REVIAL_COCHAN					13







//++++++++++++++++++++++++KOOPAS RED
//=======================================KOOPAS RED HAVE WING====================
#define KOOPAS_ANI_RED_HAVE_WING_FLYING_LEFT						0
#define KOOPAS_ANI_RED_HAVE_WING_FLYING_RIGHT						1
//=======================================END KOOPAS RED HAVE WING================

//=======================================KOOPAS RED====================
#define KOOPAS_ANI_RED_WALKING_LEFT									2
#define KOOPAS_ANI_RED_WALKING_RIGHT								3
//=======================================END KOOPAS RED================

//=======================================KOOPAS RED SHELL====================
#define KOOPAS_ANI_RED_SHELL_IDLE									4
#define KOOPAS_ANI_RED_SHELL_IDLE_OVERTURNED						5
#define KOOPAS_ANI_RED_SHELL_MOVE									6
#define KOOPAS_ANI_RED_SHELL_MOVE_OVERTURNED						7
#define KOOPAS_ANI_RED_SHELL_HEALTH									8
#define KOOPAS_ANI_RED_SHELL_HEALTH_OVERTURNED						9
//=======================================END KOOPAS RED SHELL================
//++++++++++++++++++++++++KOOPAS GREEN
//=======================================KOOPAS GREEN HAVE WING====================
#define KOOPAS_ANI_GREEN_HAVE_WING_FLYING_LEFT						10
#define KOOPAS_ANI_GREEN_HAVE_WING_FLYING_RIGHT						11
//=======================================END KOOPAS GREEN HAVE WING================

//=======================================KOOPAS GREEN====================
#define KOOPAS_ANI_GREEN_WALKING_LEFT									12
#define KOOPAS_ANI_GREEN_WALKING_RIGHT								13
//=======================================END KOOPAS GREEN================

//=======================================KOOPAS GREEN SHELL====================
#define KOOPAS_ANI_GREEN_SHELL_IDLE									14
#define KOOPAS_ANI_GREEN_SHELL_IDLE_OVERTURNED						15
#define KOOPAS_ANI_GREEN_SHELL_MOVE									16
#define KOOPAS_ANI_GREEN_SHELL_MOVE_OVERTURNED						17
#define KOOPAS_ANI_GREEN_SHELL_HEALTH								18
#define KOOPAS_ANI_GREEN_SHELL_HEALTH_OVERTURNED					19
//=======================================END KOOPAS GREEN SHELL================


//=======================================KOOPAS GREEN SHELL====================
#define KOOPAS_GREEN_ANI_SHELL_REVIAL_KHONGCHAN					20
#define KOOPAS_GREEN_ANI_SHELL_REVIAL_COCHAN					21
#define KOOPAS_GREEN_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN		22
#define KOOPAS_GREEN_ANI_SHELL_OVERTURNED_REVIAL_COCHAN			23
//=======================================END KOOPAS GREEN SHELL================

//=======================================KOOPAS GREEN SHELL====================
#define KOOPAS_RED_ANI_SHELL_REVIAL_KHONGCHAN					25
#define KOOPAS_RED_ANI_SHELL_REVIAL_COCHAN						24
#define KOOPAS_RED_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN		26
#define KOOPAS_RED_ANI_SHELL_OVERTURNED_REVIAL_COCHAN			27
//=======================================END KOOPAS GREEN SHELL================




using namespace std;
class CKoopasGeneral
{
	static CKoopasGeneral* __instance;
	int IndexBBox;
public:
	CKoopasGeneral();
	vector<int> listAni_koopas_red;
	vector<int> listAni_koopas_green;
	void LoadListAni();
	int GetAni_Koopas(int type, int index);
	void GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int level);
	static CKoopasGeneral* GetInstance();
};