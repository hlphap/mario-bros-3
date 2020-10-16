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
	}
}

int CMarioGeneral::GetAni_Mario(int index)
{
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
	}
	
}

void CMarioGeneral::SetLevel(int lv)
{
	level = lv;
}

//CMarioGeneral* CMarioGeneral::GetInstance()
//{
//	if (__instance == NULL) __instance = new CMarioGeneral();
//	return __instance;
//}
