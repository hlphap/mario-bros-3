#include "TileMap.h"
#include "Textures.h"
#include "Utils.h"

TileMap::TileMap(int ID, LPCWSTR file_path_texture, LPCWSTR file_path_data, int row_texture, int col_texture, int row_data, int col_data, int width_tile, int height_tile)
{
	this->ID = ID;
	this->file_path_texture = file_path_texture;
	this->file_path_data = file_path_data;
	this->row_text = row_texture;
	this->col_text = col_texture;
	this->row_tilemap = row_data;
	this->col_tilemap = col_data;
	this->tile_width = width_tile;
	this->tile_height = height_tile;
	LoadTileMap();
	LoadMap();

}

TileMap::~TileMap()
{
}

void TileMap::LoadTileMap()
{
	//Load texture
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

void TileMap::LoadMap()
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
	fs.close();
}

void TileMap::Draw()
{
	for (UINT i = 0; i < row_tilemap; i++)
	{
		for (UINT j = firstcol; j <= lastcol; j++)
		{
			float x;
			if (isBeginMap)
				x = tile_width * (j - firstcol) + CGame::GetInstance()->GetCamPosX() - (int)(CGame::GetInstance()->GetCamPosX()) % 16;
			else
				x = tile_width * (j - firstcol) + CGame::GetInstance()->GetCamPosX() - (int)(CGame::GetInstance()->GetCamPosX()) % 16 - 16 * MAP_RESIDUAL;
			float y = tile_height * i;
			sprites->Get(tilemap[i][j])->Draw(x, y);
		}
	}
}

void TileMap::Update()
{
	if (CGame::GetInstance()->GetCamPosX() > SCREEN_WIDTH)
	{
		isBeginMap = false;
		firstcol = ((int)CGame::GetInstance()->GetCamPosX()) / 16 - MAP_RESIDUAL;
	}
	else
	{
		isBeginMap = true;
		firstcol = ((int)CGame::GetInstance()->GetCamPosX()) / 16;
	}
    lastcol = firstcol + ((SCREEN_WIDTH) / 16) + MAP_RESIDUAL;
	DebugOut(L"Last col, first col %d,%d", lastcol, firstcol);
}

int TileMap::GetWeightMap()
{
	return (col_tilemap) * tile_width;
}

int TileMap::GetHeightMap()
{
	return (row_tilemap * tile_height);
}
