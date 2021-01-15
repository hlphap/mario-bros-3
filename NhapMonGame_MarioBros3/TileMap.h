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
	int firstcol = 0;
	int lastcol = 0;
	int firstrow = 0;
	int lastrow = 0;
	int ID;
	int mapResidualX = 0;
	int mapResidualY = 0;
	CSprites* sprites = new CSprites;
	LPCWSTR file_path_texture, file_path_data;
	int col_text, row_text, col_tilemap, row_tilemap;
	int tile_width, tile_height;
	int tilemap[300][300];
public:
	TileMap();
	~TileMap();
	void LoadTileMap();
	void LoadMap();
	void Draw();
	void Update();
	int GetWeightMap();
	int GetHeightMap();

};

