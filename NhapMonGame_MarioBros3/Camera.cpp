#include "Camera.h"
#include "Utils.h"

Camera::Camera(CMario* m)
{
	this->player = m;
}

void Camera::Update()
{
	 //Update camera to follow player
	if (player->x > (CGame::GetInstance()->screen_width / 2) && player->x < TileMap::GetInstance()->GetWeightMap() - (CGame::GetInstance()->screen_width / 2))
	{
		cam_x = player->x - (CGame::GetInstance()->screen_width / 2);
	}
	
	//if (player->isInMainMap)
	//{
	//	//CAMY TOT NHAT 
	//	if (player->y > CGame::GetInstance()->screen_height / 4 && player->y < TileMap::GetInstance()->GetHeightMap() - 460)
	//	{
	//		cam_y = player->y - CGame::GetInstance()->screen_height / 4;
	//	}
	//}
	//else
	//{
	//	cam_y = 80;
	//	isInHideMap = true;
	//}

	//if (isInHideMap && player->isInMainMap)
	//{
	//	cam_y = 70;
	//	isInHideMap = false;
	//}
//DebugOut(L"Cam_y: %f", cam_y);
	CGame::GetInstance()->SetCamPos(cam_x, 0);
}
