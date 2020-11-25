#include "GoombaGeneral.h"

CGoombaGeneral* CGoombaGeneral::__instance = NULL;
CGoombaGeneral::CGoombaGeneral()
{
}
void CGoombaGeneral::LoadListAni()
{
	if (listAni_goomba_red.empty())
	{
		listAni_goomba_red.push_back(GOOMBA_ANI_RED_HAVE_WING_FLYING);		//FLy left
		listAni_goomba_red.push_back(GOOMBA_ANI_RED_MOVING);	//Fly right
		listAni_goomba_red.push_back(GOOMBA_ANI_RED_HAVE_WING_MOVING);
		listAni_goomba_red.push_back(GOOMBA_ANI_RED_DIE);				//Walk left
		listAni_goomba_red.push_back(GOOMBA_ANI_RED_DIE_BY_WEAPON);				//Walk right
	}


	if (listAni_goomba_yellow.empty())
	{
		listAni_goomba_yellow.push_back(GOOMBA_ANI_YELLOW_HAVE_WING_FLYING);		//FLy left
		listAni_goomba_yellow.push_back(GOOMBA_ANI_YELLOW_MOVING);	//Fly right
		listAni_goomba_yellow.push_back(GOOMBA_ANI_RED_HAVE_WING_MOVING);
		listAni_goomba_yellow.push_back(GOOMBA_ANI_YELLOW_DIE);				//Walk left
		listAni_goomba_yellow.push_back(GOOMBA_ANI_YELLOW_DIE_BY_WEAPON);				//Walk right
	}
}
int CGoombaGeneral::GetAni_Goomba(int type, int index)
{
	IndexBBox = index;
	switch (type)
	{
	case GOOMBA_TYPE_RED:
		return listAni_goomba_red[index];
		break;
	case GOOMBA_TYPE_YELLOW:
		return listAni_goomba_yellow[index];
		break;
	}
}
void CGoombaGeneral::GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int level)
{
}
CGoombaGeneral* CGoombaGeneral::GetInstance()
{
	if (__instance == NULL) __instance = new CGoombaGeneral();
	return __instance;
}
