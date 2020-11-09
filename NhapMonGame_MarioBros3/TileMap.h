#pragma once
#include "Game.h"
#include "Sprites.h"
#include <fstream>
#include <sstream>
#include<string>

#define MAP_RESIDUAL 5
#define NUM_COL_ON_SCREEN 50

class TileMap
{
public:
	bool isBeginMap = true;
	bool isHightMap = false;
	int firstcol;
	int lastcol;
	int ID;
	CSprites* sprites = new CSprites;
	LPCWSTR file_path_texture, file_path_data;
	int col_text, row_text, col_tilemap, row_tilemap;
	int tile_width, tile_height;
	int tilemap[300][300];
public:
	TileMap(int ID, LPCWSTR file_path_texture, LPCWSTR file_path_data, int row_texture, int col_texture, int row_data, int col_data, int width_tile, int height_tile);
	~TileMap();
	void LoadTileMap();
	void LoadMap();
	void Draw();
	void Update();
	int GetWeightMap();
	int GetHeightMap();
};

