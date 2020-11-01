#include "MarioGeneral.h"

CMarioGeneral::CMarioGeneral()
{
	
}

void CMarioGeneral::LoadListAni()
{
	if (listAni_mario_small.empty())
	{
		// Đứng yên
		listAni_mario_small.push_back(MARIO_ANI_SMALL_IDLE_LEFT);		//0
		listAni_mario_small.push_back(MARIO_ANI_SMALL_IDLE_RIGHT);		//1

		//Đi
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_LEFT);	//2	
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_RIGHT);	//3

		//Chạy
		listAni_mario_small.push_back(MARIO_ANI_SMALL_RUNNING_LEFT);	//4
		listAni_mario_small.push_back(MARIO_ANI_SMALL_RUNNING_RIGHT);	//5

		//Ngồi (mario nhỏ không ngồi)
		listAni_mario_small.push_back(MARIO_ANI_SMALL_IDLE_LEFT);	//6
		listAni_mario_small.push_back(MARIO_ANI_SMALL_IDLE_RIGHT);	//7

		//Dừng
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_STOP_LEFT);	//8
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_STOP_RIGHT);	//9

		//Bay
		listAni_mario_small.push_back(MARIO_ANI_SMALL_FLYING_LEFT);	//10
		listAni_mario_small.push_back(MARIO_ANI_SMALL_FLYING_RIGHT);	//11

		//Rơi (mario nhỏ không rơi) -> animation Bay
		listAni_mario_small.push_back(MARIO_ANI_SMALL_FLYING_LEFT);	//12
		listAni_mario_small.push_back(MARIO_ANI_SMALL_FLYING_RIGHT);	//13

		//Mario bay khi đạt tốc độ cao (chạy)
		listAni_mario_small.push_back(MARIO_ANI_SMALL_RUNNING_FLYING_LEFT);	//14
		listAni_mario_small.push_back(MARIO_ANI_SMALL_RUNNING_FLYING_RIGHT);	//15

		//Mario đá rùa -> CHƯA CÓ ANIUMATION
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_LEFT);		//16
		listAni_mario_small.push_back(MARIO_ANI_SMALL_WALKING_RIGHT);		//17


	}
	
	if (listAni_mario_big.empty())
	{
		// Đứng yên
		listAni_mario_big.push_back(MARIO_ANI_BIG_IDLE_LEFT);		//0
		listAni_mario_big.push_back(MARIO_ANI_BIG_IDLE_RIGHT);		//1

		//Đi
		listAni_mario_big.push_back(MARIO_ANI_BIG_WALKING_LEFT);	//2	
		listAni_mario_big.push_back(MARIO_ANI_BIG_WALKING_RIGHT);	//3

		//Chạy
		listAni_mario_big.push_back(MARIO_ANI_BIG_RUNNING_LEFT);	//4
		listAni_mario_big.push_back(MARIO_ANI_BIG_RUNNING_RIGHT);	//5

		//Ngồi
		listAni_mario_big.push_back(MARIO_ANI_BIG_SITTING_LEFT);	//6
		listAni_mario_big.push_back(MARIO_ANI_BIG_SITTING_RIGHT);	//7

		//Dừng
		listAni_mario_big.push_back(MARIO_ANI_BIG_WALKING_STOP_LEFT);	//8
		listAni_mario_big.push_back(MARIO_ANI_BIG_WALKING_STOP_RIGHT);	//9

		//Bay
		listAni_mario_big.push_back(MARIO_ANI_BIG_FLYING_LEFT);	//10
		listAni_mario_big.push_back(MARIO_ANI_BIG_FLYING_RIGHT);	//11

		//Rơi 
		listAni_mario_big.push_back(MARIO_ANI_BIG_FALLING_LEFT);	//12
		listAni_mario_big.push_back(MARIO_ANI_BIG_FALLING_RIGHT);	//13

		//Mario bay khi đạt tốc độ cao (chạy)
		listAni_mario_big.push_back(MARIO_ANI_BIG_RUNNING_FLYING_LEFT);	//14
		listAni_mario_big.push_back(MARIO_ANI_BIG_RUNNING_FLYING_RIGHT);	//15

		//Mario đá rùa 
		listAni_mario_big.push_back(MARIO_ANI_BIG_KICKING_LEFT);			//16
		listAni_mario_big.push_back(MARIO_ANI_BIG_KICKING_RIGHT);			//17


	}
	
	if (listAni_mario_tail.empty())
	{
		// Đứng yên
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_IDLE_LEFT);		//0
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_IDLE_RIGHT);		//1

		//Đi
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_WALKING_LEFT);	//2	
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_WALKING_RIGHT);	//3

		//Chạy
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_RUNNING_LEFT);	//4
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_RUNNING_RIGHT);	//5

		//Ngồi
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_SITTING_LEFT);	//6
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_SITTING_RIGHT);	//7

		//Dừng
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_WALKING_STOP_LEFT);	//8
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_WALKING_STOP_RIGHT);	//9

		//Bay
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_FLYING_LEFT);	//10
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_FLYING_RIGHT);	//11

		//Rơi 
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_FALLING_LEFT);	//12
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_FALLING_RIGHT);	//13

		//Mario bay khi đạt tốc độ cao (chạy)
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_RUNNING_FLYING_LEFT);	//14
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_RUNNING_FLYING_RIGHT);	//15

		//Mario đá rùa 
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_KICKING_LEFT);		//16
		listAni_mario_tail.push_back(MARIO_ANI_BIG_TAIL_KICKING_RIGHT);		//17


	}

	if (listAni_mario_fire.empty())
	{
		// Đứng yên
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_IDLE_LEFT);		//0
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_IDLE_RIGHT);		//1

		//Đi
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_WALKING_LEFT);	//2	
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_WALKING_RIGHT);	//3

		//Chạy
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_RUNNING_LEFT);	//4
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_RUNNING_RIGHT);	//5

		//Ngồi
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_SITTING_LEFT);	//6
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_SITTING_RIGHT);	//7

		//Dừng
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_WALKING_STOP_LEFT);	//8
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_WALKING_STOP_RIGHT);	//9

		//Bay
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_FLYING_LEFT);	//10
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_FLYING_RIGHT);	//11

		//Rơi 
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_FALLING_LEFT);	//12
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_FALLING_RIGHT);	//13

		//Mario bay khi đạt tốc độ cao (chạy)
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_RUNNING_FLYING_LEFT);	//14
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_RUNNING_FLYING_RIGHT);	//15

		//Mario đá rùa 
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_KICKING_LEFT);		//16
		listAni_mario_fire.push_back(MARIO_ANI_BIG_FIRE_KICKING_RIGHT);		//17


	}
}

int CMarioGeneral::GetAni_Mario(int index)
{
	IndexBBox = index;
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		return listAni_mario_small[index];
		break;
	case MARIO_LEVEL_BIG:
		return listAni_mario_big[index];
		break;
	case MARIO_LEVEL_BIG_TAIL:
		return listAni_mario_tail[index];
		break;
	case MARIO_LEVEL_BIG_FIRE:
		return listAni_mario_fire[index];
		break;
	}
	
}

void CMarioGeneral::GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int nx)
{
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		//left top khong doi
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
		break;
	case MARIO_LEVEL_BIG:
		if (nx > 0) 
			left = left + 3;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
		break;
	case MARIO_LEVEL_BIG_TAIL:
		left += 8;
		right = left + MARIO_BIG_TAIL_BBOX_WIDTH;
		bottom = top + MARIO_BIG_TAIL_BBOX_HEIGHT;
		break;
	case MARIO_LEVEL_BIG_FIRE:
		if (nx > 0)
			left = left + 3;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
		break;
	}
	if ((IndexBBox == MARIO_ANI_SITTING_LEFT) || (IndexBBox == MARIO_ANI_SITTING_RIGHT))
		top = top + 8;
}

void CMarioGeneral::SetLevel(int lv)
{
	level = lv;
}

CMarioGeneral* CMarioGeneral::__instance = NULL;

CMarioGeneral* CMarioGeneral::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioGeneral();
	return __instance;
}
