#include "KoopasGeneral.h"



CKoopasGeneral::CKoopasGeneral()
{
}
void CKoopasGeneral::LoadListAni()
{
	if (listAni_koopas_red.empty())
	{
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_HAVE_WING_FLYING_LEFT);		//FLy left
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_HAVE_WING_FLYING_RIGHT);	//Fly right
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_WALKING_LEFT);				//Walk left
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_WALKING_RIGHT);				//Walk right
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_IDLE);				//Shell idle
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_IDLE_OVERTURNED);		//Shell idle overturned
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_MOVE);				//Shell move
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_MOVE_OVERTURNED);		//Shell move overturned
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_HEALTH);				//Shell health //KHONG DUNG
		listAni_koopas_red.push_back(KOOPAS_ANI_RED_SHELL_HEALTH_OVERTURNED);	//Shell health overturned // KHONG DUNG
		listAni_koopas_red.push_back(KOOPAS_RED_ANI_SHELL_REVIAL_KHONGCHAN);	//revial khong chan
		listAni_koopas_red.push_back(KOOPAS_RED_ANI_SHELL_REVIAL_COCHAN);	//revial co chan
		listAni_koopas_red.push_back(KOOPAS_RED_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN); //overturned khong chan
		listAni_koopas_red.push_back(KOOPAS_RED_ANI_SHELL_OVERTURNED_REVIAL_COCHAN);	//overturned co chan
	}
	
	
	if (listAni_koopas_green.empty())
	{
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_HAVE_WING_FLYING_LEFT)	;		//FLy left
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_HAVE_WING_FLYING_RIGHT);	//Fly right
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_WALKING_LEFT);				//Walk left
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_WALKING_RIGHT);				//Walk right
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_IDLE);					//Shell idle
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_IDLE_OVERTURNED);		//Shell idle overturned
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_MOVE);					//Shell move
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_MOVE_OVERTURNED);		//Shell move overturned
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_HEALTH);				//Shell health
		listAni_koopas_green.push_back(KOOPAS_ANI_GREEN_SHELL_HEALTH_OVERTURNED);		//Shell health overturned
		listAni_koopas_green.push_back(KOOPAS_GREEN_ANI_SHELL_REVIAL_KHONGCHAN);	//revial khong chan
		listAni_koopas_green.push_back(KOOPAS_GREEN_ANI_SHELL_REVIAL_COCHAN);	//revial co chan
		listAni_koopas_green.push_back(KOOPAS_GREEN_ANI_SHELL_OVERTURNED_REVIAL_KHONGCHAN); //overturned khong chan
		listAni_koopas_green.push_back(KOOPAS_GREEN_ANI_SHELL_OVERTURNED_REVIAL_COCHAN);	//overturned co chan
	}
}

int CKoopasGeneral::GetAni_Koopas(int type, int index)
{
	IndexBBox = index;
	switch (type)
	{
	case KOOPAS_TYPE_RED:
		return listAni_koopas_red[index];
		break;
	case KOOPAS_TYPE_GREEN:
		return listAni_koopas_green[index];
		break;
	}
}

void CKoopasGeneral::GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int level)
{
	switch (level)
	{
	case KOOPAS_LEVEL_HAVE_WING:
		//left top khong doi
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
		break;
	case KOOPAS_LEVEL_DEFAULT:
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
		break;
	case KOOPAS_LEVEL_SHELL:
		top = top + KOOPAS_BBOX_HEIGHT_SLEEP;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
		break;
	}
}


//Singleton
CKoopasGeneral* CKoopasGeneral::__instance = NULL;

CKoopasGeneral* CKoopasGeneral::GetInstance()
{
	if (__instance == NULL) __instance = new CKoopasGeneral();
	return __instance;
}