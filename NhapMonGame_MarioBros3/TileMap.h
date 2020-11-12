#pragma once
#include "Game.h"
#include "Sprites.h"
#include <fstream>
#include <sstream>
#include<string>

#define MAP_RESIDUAL 5

class TileMap
{
public:
	bool isBeginMapX = true;
	bool isBeginMapY = false;
	int firstcol;
	int lastcol;
	int firstrow;
	int lastrow;
	int ID;
	int mapResidualX = 5;
	CSprites* sprites = new CSprites;
	LPCWSTR file_path_texture, file_path_data;
	int col_text, row_text, col_tilemap, row_tilemap;
	int tile_width, tile_height;
	int tilemap[300][300];
	static TileMap* __instance;
public:
	TileMap();
	~TileMap();
	void LoadTileMap();
	void LoadMap();
	void Draw();
	void Update();
	int GetWeightMap();
	int GetHeightMap();
	static TileMap* GetInstance();
};

