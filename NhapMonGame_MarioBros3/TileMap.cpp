#include "TileMap.h"
#include "Textures.h"
#include "Utils.h"


TileMap::TileMap()
{	
}

TileMap::~TileMap()
{
}

void TileMap::LoadTileMap()
{
	//Load texture
	if (__instance != NULL)
	{
		CTextures* texture = CTextures::GetInstance();
		texture->Add(ID, file_path_texture, D3DCOLOR_XRGB(255, 0, 255));
		LPDIRECT3DTEXTURE9 textileMap = texture->Get(ID);

		int idSprite = 1;
		for (UINT i = 0; i < row_text; i++)
		{
			for (UINT j = 0; j < col_text; j++)
			{
				sprites->Add(idSprite, tile_width * j, tile_width * i, tile_width * (j + 1), tile_height * (i + 1), textileMap);
				idSprite = idSprite + 1;
			}
		}
	}
}

void TileMap::LoadMap()
{
	if (__instance != NULL)
	{
		ifstream fs(file_path_data, ios::in);
		if (fs.fail())
		{
			fs.close();
			return;
		}
		DebugOut(L"row %d", row_tilemap);
		DebugOut(L"\ncol %d", col_tilemap);
		for (int i = 0; i < row_tilemap; i++)
		{
			for (int j = 0; j < col_tilemap; j++)
			{
				fs >> tilemap[i][j];
				DebugOut(L"\ni,j %d,%d", i, j);
				DebugOut(L"\ttilemap[i][j] = %d", tilemap[i][j]);
			}
		}
		fs.close();
	}	
}

void TileMap::Draw()
{

	if (__instance != NULL)
	{
		for (UINT i = firstrow; i < lastrow; i++)
		{
			for (UINT j = firstcol; j < lastcol; j++)
			{
				float x;
				float y;
				if (isBeginMapX)
				{
					x = tile_width * (j - firstcol) + CGame::GetInstance()->GetCamPosX() - (int)(CGame::GetInstance()->GetCamPosX()) % tile_width;	
				}
				else
				{
					x = tile_width * (j - firstcol) +CGame::GetInstance()->GetCamPosX() - (int)(CGame::GetInstance()->GetCamPosX()) % tile_width - tile_width * mapResidualX;
				
				}
					
				if (isBeginMapY)
					y = tile_height * (i - firstrow) + CGame::GetInstance()->GetCamPosY() - (int)(CGame::GetInstance()->GetCamPosY()) % tile_height;
				else
					y = tile_height * (i - firstrow) + CGame::GetInstance()->GetCamPosY() - (int)(CGame::GetInstance()->GetCamPosY()) % tile_height - tile_width * mapResidualY;
				sprites->Get(tilemap[i][j])->Draw(x, y);
			}
		}
	}
	
}

void TileMap::Update()
{

	if (__instance != NULL)
	{
		//Truc x, firstcol, lastcol
		if (CGame::GetInstance()->GetCamPosX() > 0) // Cam X bat dau di chuyen
		{
			mapResidualX = CGame::GetInstance()->GetCamPosX() / 16;
			if (mapResidualX > MAP_RESIDUAL) mapResidualX = MAP_RESIDUAL;
			isBeginMapX = false;
			firstcol = ((int)CGame::GetInstance()->GetCamPosX()) / 16 - mapResidualX;
		}
		else
		{
			isBeginMapX = true;
			firstcol = ((int)CGame::GetInstance()->GetCamPosX()) / 16;
		}
		lastcol = firstcol + (SCREEN_WIDTH / tile_width) + mapResidualX*2;

		//Truc y, firstrow, lastrow
		if (CGame::GetInstance()->GetCamPosY() > 0)
		{
			mapResidualY = CGame::GetInstance()->GetCamPosY() / 16;
			if (mapResidualY > 2) mapResidualY = 2;
			isBeginMapY = false;
			firstrow = (int)CGame::GetInstance()->GetCamPosY() / 16 - mapResidualY;

		}
		else
		{
			//DebugOut(L"true");
			isBeginMapY = true;
			firstrow = (int)CGame::GetInstance()->GetCamPosY() / 16;
		}
		lastrow = firstrow + SCREEN_HEIGHT / 16 + mapResidualY *2;
		DebugOut(L"\nCam Y%f", CGame::GetInstance()->GetCamPosY());
		DebugOut(L"\nfirst ROW: %d", firstrow);
		DebugOut(L"\nlast ROW: %d", lastrow);
	}
	
}

int TileMap::GetWeightMap()
{
	if (__instance != NULL)
		return (col_tilemap - 5)*tile_width;
	else
		return -1;
}

int TileMap::GetHeightMap()
{
	if (__instance != NULL)
		return ((row_tilemap - 5)* tile_height);
	else
		return -1;
}

TileMap * TileMap::__instance = NULL;

TileMap* TileMap::GetInstance()
{
	if (__instance == NULL) __instance = new TileMap();
	return __instance;
}
