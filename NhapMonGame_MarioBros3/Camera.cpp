#include "Camera.h"
#include "Utils.h"

Camera::Camera(CMario* m, int typeCamera)
{
	this->player = m;
	this->typeCamera = typeCamera;
	vx = CAMERA_SPEED_X;
}

void Camera::Update(DWORD dt)
{
	if (typeCamera == 0)
	{
		cam_x = 0;
		cam_y = 0;
	}
	else if (typeCamera == 1)  //Update camera to follow player
	{
		if (player->x > (CGame::GetInstance()->screen_width / 2) && player->x < mapW - (CGame::GetInstance()->screen_width / 2))
		{
			cam_x = player->x - (CGame::GetInstance()->screen_width / 2);
		}

		if (player->isInMainMap)
		{
			//CAMY TOT NHAT 
			if (player->y > CGame::GetInstance()->screen_height / 4 && player->y < mapH - 350)
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
	/*	if (player->x > (CGame::GetInstance()->screen_width / 2) && player->x < mapW - (CGame::GetInstance()->screen_width / 2))
		{
			cam_x = player->x - (CGame::GetInstance()->screen_width / 2);
		}*/
		cam_x += vx *dt;
		//DebugOut(L"player->x: %f", player->x);
		if (cam_x > 1778 && cam_x < 1800)
		{
			cam_x = 1778.0f; //Lock Cam On End Pipe
		}
		else
		if (cam_x > 1800)
		{
			cam_x = player->x - (CGame::GetInstance()->screen_width / 4);
			if (player->x > (CGame::GetInstance()->screen_width / 4) && player->x + (CGame::GetInstance()->screen_width / 4) < 2528)
			{
				cam_x = player->x - (CGame::GetInstance()->screen_width / 4);
				if (cam_x < 2048) //Look cam First EndScene
					cam_x = 2048;
			}
			if (cam_x > 2290) //Look Cam Last EndScene
				cam_x = 2290;
		}
		cam_y = 240.0f;
	}
	CGame::GetInstance()->SetCamPos((cam_x), (cam_y));
}
