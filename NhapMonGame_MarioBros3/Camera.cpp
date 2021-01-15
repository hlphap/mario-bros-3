#include "Camera.h"
#include "Utils.h"

Camera::Camera(CMario* m, TileMap *map, int typeCamera)
{
	this->player = m;
	this->map = map;
	this->typeCamera = typeCamera;
	vx = CAMERA_SPEED_X;
}

void Camera::Update(DWORD dt)
{
	//DebugOut(L"\ntype Camera: %d", typeCamera);
	//Camera Default = 0
	if (typeCamera == 0)
	{
		cam_x = 0;
		cam_y = 0;
	}
	else if (typeCamera == 1)  //Update camera to follow player
	{
		if (player->x > (CGame::GetInstance()->screen_width / 2) && player->x < map->GetWeightMap() - (CGame::GetInstance()->screen_width / 2))
		{
			cam_x = player->x - (CGame::GetInstance()->screen_width / 2);
		}

		if (player->isInMainMap)
		{
			//CAMY TOT NHAT 
			if (player->y > CGame::GetInstance()->screen_height / 4 && player->y < map->GetHeightMap() - 350)
			{
				cam_y = player->y - CGame::GetInstance()->screen_height / 4;
			}
		}
		else
		{
			cam_y = 460;
			isInHideMap = true;
		}
		if (isInHideMap && player->isInMainMap)
		{
			cam_y = 244.296234;
			isInHideMap = false;
		}
	}
	else if (typeCamera == 2)
	{
		//cam_x += vx * dt;
		if (player->x > (CGame::GetInstance()->screen_width / 2) && player->x < map->GetWeightMap() - (CGame::GetInstance()->screen_width / 2))
		{
			cam_x = player->x - (CGame::GetInstance()->screen_width / 2);
		}

		cam_y = 240.0f;
	}
	
	CGame::GetInstance()->SetCamPos(cam_x, cam_y);
}
