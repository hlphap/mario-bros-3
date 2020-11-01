#pragma once
#include <vector>
#include <istream>


#define MARIO_STATE_IDLE								0
#define MARIO_STATE_WALKING_RIGHT						100
#define MARIO_STATE_WALKING_LEFT						200
#define MARIO_STATE_JUMPING								300
#define MARIO_ANI_SHORT_JUMP							301
#define MARIO_STATE_BIG_TAIL_KEEP_JUMP_FALL_SLOW		302
#define MARIO_STATE_BIG_TAIL_KEEP_JUMP_FLY_HIGHT		303
#define MARIO_STATE_FALLING								310
#define MARIO_STATE_DIE									400
#define MARIO_STATE_SITTING								500
#define MARIO_STATE_STOP_SITTING						501
#define MARIO_STATE_WALKING								600
#define MARIO_STATE_NOT_WALKING							601
#define MARIO_STATE_RUNNING								700
#define MARIO_STATE_STOP_RUNNING						701
#define MARIO_STATE_DECREASE_WHEN_RUNNING				702
#define MARIO_STATE_BIG_TAIL_ATTACK						800
#define MARIO_STATE_BIG_FIRE_ATTACK						900
#define MARIO_STATE_KICK								1000

//================================MARIO ANIMATION GENERAL ZONE=================================
//end defaul
#define MARIO_ANI_IDLE_LEFT								0
#define MARIO_ANI_IDLE_RIGHT							1
#define MARIO_ANI_WALKING_LEFT							2
#define MARIO_ANI_WALKING_RIGHT							3
#define MARIO_ANI_RUNNING_LEFT							4
#define MARIO_ANI_RUNNING_RIGHT							5
#define MARIO_ANI_SITTING_LEFT							6
#define MARIO_ANI_SITTING_RIGHT							7
#define MARIO_ANI_WALKING_STOP_LEFT						8
#define MARIO_ANI_WALKING_STOP_RIGHT					9
#define MARIO_ANI_FLYING_LEFT							10
#define MARIO_ANI_FLYING_RIGHT							11
#define MARIO_ANI_FALLING_LEFT							12
#define MARIO_ANI_FALLING_RIGHT							13
#define MARIO_ANI_RUNNING_FLY_LEFT						14
#define MARIO_ANI_RUNNING_FLY_RIGHT						15
#define MARIO_ANI_KICKING_LEFT							16
#define MARIO_ANI_KICKING_RIGHT							17


////================================END MARIO ANIMATION GENERAL ZONE=================================

//================================IDLE GENERAL ZONE=================================
#define MARIO_ANI_BIG_IDLE_RIGHT						0
#define MARIO_ANI_BIG_IDLE_LEFT							1
#define MARIO_ANI_SMALL_IDLE_RIGHT						2
#define MARIO_ANI_SMALL_IDLE_LEFT						3
#define MARIO_ANI_BIG_TAIL_IDLE_RIGHT					19
#define MARIO_ANI_BIG_TAIL_IDLE_LEFT					20
#define MARIO_ANI_BIG_FIRE_IDLE_RIGHT					69
#define MARIO_ANI_BIG_FIRE_IDLE_LEFT					70
//================================END IDLE GENERAL ZONE=================================
//================================WALKING GENERAL ZONE=================================
#define MARIO_ANI_BIG_WALKING_RIGHT						4
#define MARIO_ANI_BIG_WALKING_LEFT						5
#define MARIO_ANI_BIG_TAIL_WALKING_RIGHT				21
#define MARIO_ANI_BIG_TAIL_WALKING_LEFT					22
#define MARIO_ANI_BIG_FIRE_WALKING_RIGHT				51
#define MARIO_ANI_BIG_FIRE_WALKING_LEFT					52
#define MARIO_ANI_SMALL_WALKING_RIGHT					6
#define MARIO_ANI_SMALL_WALKING_LEFT					7
//================================END WALKING GENERAL ZONE=================================
//================================RUNNING GENERAL ZONE=================================
#define MARIO_ANI_BIG_RUNNING_RIGHT						37
#define MARIO_ANI_BIG_RUNNING_LEFT						38
#define MARIO_ANI_BIG_TAIL_RUNNING_RIGHT				39
#define MARIO_ANI_BIG_TAIL_RUNNING_LEFT					40
#define MARIO_ANI_BIG_FIRE_RUNNING_RIGHT				63
#define MARIO_ANI_BIG_FIRE_RUNNING_LEFT					64
#define MARIO_ANI_SMALL_RUNNING_RIGHT					35
#define MARIO_ANI_SMALL_RUNNING_LEFT					36
//================================END RUNNING GENERAL ZONE=================================

//================================SITTING GENERAL ZONE=================================
#define MARIO_ANI_DIE									8
#define MARIO_ANI_BIG_SITTING_LEFT						9
#define MARIO_ANI_BIG_SITTING_RIGHT						10
#define MARIO_ANI_BIG_TAIL_SITTING_RIGHT				23
#define MARIO_ANI_BIG_TAIL_SITTING_LEFT					24
#define MARIO_ANI_BIG_FIRE_SITTING_RIGHT				53
#define MARIO_ANI_BIG_FIRE_SITTING_LEFT					54
//================================END SITTING GENERAL ZONE=================================

//================================STOP GENERAL ZONE=================================
#define MARIO_ANI_BIG_WALKING_STOP_LEFT					13
#define MARIO_ANI_BIG_WALKING_STOP_RIGHT				14	
#define MARIO_ANI_BIG_TAIL_WALKING_STOP_LEFT			25
#define MARIO_ANI_BIG_TAIL_WALKING_STOP_RIGHT			26
#define MARIO_ANI_BIG_FIRE_WALKING_STOP_LEFT			55
#define MARIO_ANI_BIG_FIRE_WALKING_STOP_RIGHT			56
#define MARIO_ANI_SMALL_WALKING_STOP_LEFT				15
#define MARIO_ANI_SMALL_WALKING_STOP_RIGHT				16	
//================================END STOP GENERAL ZONE=================================

//================================FLYING GENERAL ZONE=================================
#define MARIO_ANI_BIG_FLYING_RIGHT						11
#define MARIO_ANI_BIG_FLYING_LEFT						12
#define MARIO_ANI_SMALL_FLYING_RIGHT					17	
#define MARIO_ANI_SMALL_FLYING_LEFT						18
#define MARIO_ANI_BIG_TAIL_FLYING_RIGHT					27
#define MARIO_ANI_BIG_TAIL_FLYING_LEFT					28
#define MARIO_ANI_BIG_FIRE_FLYING_RIGHT					57
#define MARIO_ANI_BIG_FIRE_FLYING_LEFT					58
//================================END FLYING GENERAL ZONE=================================
//================================MARIO FALLING GENERAL ZONE=================================
#define MARIO_ANI_BIG_FALLING_RIGHT						29
#define MARIO_ANI_BIG_FALLING_LEFT						30
#define MARIO_ANI_BIG_TAIL_FALLING_RIGHT				31
#define MARIO_ANI_BIG_TAIL_FALLING_LEFT					32
#define MARIO_ANI_BIG_FIRE_FALLING_RIGHT				59
#define MARIO_ANI_BIG_FIRE_FALLING_LEFT					60
//================================END MARIO FALLING GENERAL ZONE=================================

//================================MARIO ATTACKING GENERAL ZONE=================================
#define MARIO_ANI_BIG_TAIL_ATTACKING_RIGHT				33
#define MARIO_ANI_BIG_TAIL_ATTACKING_LEFT				34
#define MARIO_ANI_BIG_FIRE_ATTACKING_RIGHT				61
#define MARIO_ANI_BIG_FIRE_ATTACKING_LEFT				62
//================================FLYING WHEN RUNNING GENERAL ZONE=================================
#define MARIO_ANI_BIG_RUNNING_FLYING_RIGHT				41
#define MARIO_ANI_BIG_RUNNING_FLYING_LEFT				42
#define MARIO_ANI_BIG_TAIL_RUNNING_FLYING_RIGHT			43
#define MARIO_ANI_BIG_TAIL_RUNNING_FLYING_LEFT			44
#define MARIO_ANI_BIG_FIRE_RUNNING_FLYING_RIGHT			65
#define MARIO_ANI_BIG_FIRE_RUNNING_FLYING_LEFT			66
#define MARIO_ANI_SMALL_RUNNING_FLYING_RIGHT			45
#define MARIO_ANI_SMALL_RUNNING_FLYING_LEFT				46
//================================END FLYING WHEN RUNNING  ZONE=================================

//================================KICKING GENERAL ZONE=================================
#define MARIO_ANI_BIG_KICKING_RIGHT						77
#define MARIO_ANI_BIG_KICKING_LEFT						78
#define MARIO_ANI_BIG_TAIL_KICKING_RIGHT				75
#define MARIO_ANI_BIG_TAIL_KICKING_LEFT					76
#define MARIO_ANI_BIG_FIRE_KICKING_RIGHT				74
#define MARIO_ANI_BIG_FIRE_KICKING_LEFT					73
//================================KICKING GENERAL ZONE=================================

//================================FALLING  SLOWNLY WHEN SPACE ENTER GENERAL ZONE=================================
#define MARIO_ANI_BIG_TAIL_FALLING_SLOW_RIGHT			47
#define MARIO_ANI_BIG_TAIL_FALLING_SLOW_LEFT			48
//================================END FALLING  SLOWNLY WHEN SPACE ENTER   ZONE=================================

//================================RUNNING FAILLING WHEN SPACE=================================
#define MARIO_ANI_BIG_TAIL_RUNNING_FALLING_RIGHT		49
#define MARIO_ANI_BIG_TAIL_RUNNING_FALLING_LEFT			50
//================================END RUNNING FAILLING  ZONE=================================

//================================FLYING  WHEN SPACE ENTER GENERAL ZONE=================================
#define MARIO_ANI_BIG_TAIL_FLYING_SLOW_RIGHT			71
#define MARIO_ANI_BIG_TAIL_FLYING_SLOW_LEFT				72	
//================================END FALLING  SLOWNLY WHEN SPACE ENTER   ZONE=================================

//================================RUNNING FAILLING WHEN SPACE=================================
#define MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_RIGHT		67
#define MARIO_ANI_BIG_FIRE_FLYING_ATTACKING_LEFT		68
//================================END RUNNING FAILLING  ZONE=================================
//================================MARIO LEVEL GENERAL ZONE=================================
#define	MARIO_LEVEL_SMALL								1
#define	MARIO_LEVEL_BIG									2
#define	MARIO_LEVEL_BIG_TAIL							3
#define	MARIO_LEVEL_BIG_FIRE							4

//================================MARIO RENDER BOX GENERAL ZONE=================================
#define MARIO_BIG_BBOX_WIDTH							15
#define MARIO_BIG_BBOX_HEIGHT							28
#define MARIO_BIG_TAIL_BBOX_WIDTH						15
#define MARIO_BIG_TAIL_BBOX_HEIGHT						28
#define MARIO_BIG_BBOX_SITTING_HEIGHT					14
#define MARIO_BIG_TAIL_BBOX_SITTING_HEIGHT				20
#define MARIO_SMALL_BBOX_WIDTH							13
#define MARIO_SMALL_BBOX_HEIGHT							15


//================================ANOTHER GENERAL ZONE=================================
#define MARIO_UNTOUCHABLE_TIME							5000
#define MARIO_RATIO_WHEN_SPEEPUPING					0.75f
#define MARIO_RATIO_WHEN_SPEED_MAX					0.01f
#define MARIO_RATIO_WHEN_KEEP_JUMPPING				0.5f
#define MARIO_UNTOUCHABLE_TIME							1000
#define KOOPAS_MAX_HEALTH								2
#define MARIO_TIME_ALLOWED_FLY							500
#define MARIO_TIME_FLYING_MAX							4500
#define MARIO_TIME_KICK									200
#define MARIO_TIME_BIG_TAIL_ATTACK						375
#define MARIO_TIME_BIG_FIRE_ATTACK_ON_GROUND			75
#define MARIO_TIME_BIG_FIRE_ATTACK_ON_AIR				200



//D
#define MARIO_D_HEED_TO_HAND_ATTACK						7
#define MARIO_D_HEED_TO_TAIL_ATTACK						16

using namespace std;
class CMarioGeneral
{
	static CMarioGeneral* __instance;
	int level;
	int IndexBBox;
public:
	CMarioGeneral();
	vector<int> listAni_mario_small;
	vector<int> listAni_mario_big;
	vector<int> listAni_mario_tail;
	vector<int> listAni_mario_fire;
	void LoadListAni();
	int GetAni_Mario(int index);
	void GetBoundingBoxFromGroupAni(float& left, float& top, float& right, float& bottom, int nx);
	void SetLevel(int lv);
	static CMarioGeneral* GetInstance();
};

