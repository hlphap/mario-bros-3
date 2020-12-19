#pragma once
#include "Game.h"
#include "Sprites.h"
#include <fstream>
#include <sstream>
#include<string>

#define MAP_RESIDUALX 5
#define MAP_RESIDUALY 2

class TileMap
{
public:
	float screenWidth;
	float screenHeight;
	int firstcol;
	int lastcol;
	int firstrow;
	int lastrow;
	int ID;
	int mapResidualX = 0;
	int mapResidualY = 0;
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

