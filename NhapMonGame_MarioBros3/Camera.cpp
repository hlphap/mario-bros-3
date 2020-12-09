#include "Camera.h"

Camera::Camera(CMario* m)
{
	this->player = m;
}

void Camera::Update()
{
	// Update camera to follow player
	float cx, cy;
	if (player->x > (SCREEN_WIDTH / 2) && player->x < TileMap::GetInstance()->GetWeightMap() - (SCREEN_WIDTH / 2))
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		cam_x = cx;
	}

	//CAMY TOT NHAT 
	if (player->y > SCREEN_HEIGHT / 3 && player->y < TileMap::GetInstance()->GetHeightMap() - SCREEN_HEIGHT * 2 / 3)
	{
		cy = player->y - SCREEN_HEIGHT / 3 + MARIO_BIG_BBOX_HEIGHT;
		cam_y = cy;
	}
	CGame::GetInstance()->SetCamPos(cam_x, cam_y);
}
