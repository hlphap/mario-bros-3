#include "TileMap.h"
#include "Textures.h"
#include "Utils.h"



TileMap::TileMap()
{
	screenWidth = CGame::GetInstance()->screen_width;
	screenHeight = CGame::GetInstance()->screen_height;
}

TileMap::~TileMap()
{
}

void TileMap::LoadTileMap()
{
		CTextures* texture = CTextures::GetInstance();
		texture->Add(ID, file_path_texture, D3DCOLOR_XRGB(255, 255, 255));
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

void TileMap::LoadMap(Grid*grid)
{
		ifstream fs(file_path_data, ios::in);
		if (fs.fail())
		{
			fs.close();
			return;
		}
		for (int i = 0; i < row_tilemap; i++)
		{
			for (int j = 0; j < col_tilemap; j++)
			{
				fs >> tilemap[i][j];
			}
		}
		int section;
		char str[1024];
		while (fs.getline(str, 1024))
		{
			string line(str);
			if (line == "[MAP_INFOR]")
			{
				section = MAP_INFOR;
				continue;
			}
			else
				if (line == "[OBJECTS]")
				{
					section = OBJECCTS;
					continue;
				}
			if (line == "" || line[0] == '#') continue;
			else
			{
				if (section == MAP_INFOR)
				{
					vector<string> tokens = split(line);
					CGame::GetInstance()->cellW = atoi(tokens[0].c_str());
					CGame::GetInstance()->cellH = atoi(tokens[1].c_str());
					grid->cellWidth = CGame::GetInstance()->cellW;
					grid->cellHeight = CGame::GetInstance()->cellH;
					grid->GridResize();
				}
				else
					if (section == OBJECCTS)
						grid->InsertObjToGrid(line);

			}
		}
		fs.close();
}




void TileMap::Update()
{
	if (CGame::GetInstance()->GetCamPosX() < 0)
	{
		firstcol = (int)CGame::GetInstance()->GetCamPosX() / tile_width;
	}
	else //Khi camera di chuyen
	{
		mapResidualX = (ceil)(CGame::GetInstance()->GetCamPosX() / tile_width);
		if (mapResidualX > MAP_RESIDUALX)
		{
			mapResidualX = MAP_RESIDUALX;
			firstcol = (int)CGame::GetInstance()->GetCamPosX() / tile_width - mapResidualX;
		}
		
	}
	lastcol = firstcol + (screenWidth / tile_width) + mapResidualX * 2;
	
	if (CGame::GetInstance()->GetCamPosY() < 0)
	{
		firstrow = (int)CGame::GetInstance()->GetCamPosY() / tile_height;
	}
	else //Cam Y di chuyen
	{
		mapResidualY = (int)CGame::GetInstance()->GetCamPosY() / tile_height;
		if (mapResidualY > MAP_RESIDUALY) mapResidualY = MAP_RESIDUALY;
		firstrow = (int)CGame::GetInstance()->GetCamPosY() / tile_height - mapResidualY;
	}
	lastrow = firstrow + (screenHeight / tile_height) + mapResidualY * 2;
}


void TileMap::Draw()
{
	for (int i = firstrow; i < lastrow; i++)
	{
		for (int j = firstcol; j < lastcol; j++)
		{
			float x = j * tile_width;
			float y = i * tile_height;
			sprites->Get(tilemap[i][j])->Draw(x,y,255);
		}
	}
}


int TileMap::GetWeightMap()
{
	return (col_tilemap - 5)*tile_width;
}

int TileMap::GetHeightMap()
{
	return ((row_tilemap - 5)* tile_height);
}

//TileMap * TileMap::__instance = NULL;

//TileMap* TileMap::GetInstance()
//{
//	if (__instance == NULL) __instance = new TileMap();
//	return __instance;
//}
