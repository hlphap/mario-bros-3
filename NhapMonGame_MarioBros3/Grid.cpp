#include "Grid.h"
#include "Utils.h"


void Grid::UpdateGrid(vector<LPGAMEOBJECT> listObj, vector<LPGAMEOBJECT> listEnemy)
{
	
	ClearGrid();

	for (int i = 0; i < listEnemy.size(); i++)
	{
		float l, t, r, b;
		listEnemy[i]->GetBoundingBox(l, t, r, b);
		int Top = int(t / cellHeight);
		int Left = int(l / cellWidth);
		int Right = ceil(r / cellWidth);
		int Bottom = ceil(b / cellHeight);
		if (listEnemy[i]->isActive)
		{
			for (int row = Top; row < Bottom; row++)
				for (int col = Left; col < Right; col++)
				{
					cell[row][col].push_back(listEnemy[i]);
				}
		}
	}	
	for (int i = 0; i < listObj.size(); i++)
	{
		float l, t, r, b;
		listObj[i]->GetBoundingBox(l, t, r, b);
		int Top = int(t / cellHeight);
		int Left = int(l / cellWidth);
		int Right = ceil(r / cellWidth);
		int Bottom = ceil(b / cellHeight);
		if (listObj[i]->isActive && listObj[i]->category == CATEGORY::GROUND)
		{
			for (int row = Top; row < Bottom; row++)
				for (int col = Left; col < Right; col++)
				{
					cell[row][col].push_back(listObj[i]);
					//DebugOut(L"row, col : %d, %d", row, col);
				}
		}
	}
}

Grid::Grid(TileMap *map, Camera *cam) // Khoi tao Cell, Row Col
{
	this->map = map;
	int y = map->GetWeightMap();
	int x = map->GetHeightMap();
	this->cam = cam;
	cellWidth = 187;//CGame::GetInstance()->screen_width / 2;
	cellHeight = 328;//CGame::GetInstance()->screen_height / 2;
	numRow = (map->GetHeightMap() + cellHeight)/ cellHeight;
	numCol = (map->GetWeightMap() + cellWidth) / cellWidth;
	//this->mario = mario;
	cell.resize(numRow+1);
	for (int i = 0; i < numRow+1; i++)
		cell[i].resize(numCol+1);

	ClearGrid(); // Clear Grid
}

void Grid::GetListObj(vector<LPGAMEOBJECT>& listMapObj, vector<LPGAMEOBJECT>& listEnemy) //Get listMapObj, Get listEnemy on Grid NearCamera
{
	int firstCol = (int)(cam->GetCamPosX() / cellWidth);
	int lastCol = ceil((cam->GetCamPosX() + CGame::GetInstance()->screen_width) / cellWidth);

	int firstRow = (int)(cam->GetCamPosY() / cellHeight);
	int lastRow = ceil((cam->GetCamPosY() + CGame::GetInstance()->screen_height) / cellHeight);

	//Get Obj Can Update
	for (int i = firstRow; i < lastRow; i++)
	{
		for (int j = firstCol; j < lastCol; j++)
		{
			for (int k = 0; k < cell[i][j].size(); k++)
			{
				if (cell[i][j][k]->isActive && !cell[i][j][k]->inGrid)
				{
					if (cell[i][j][k]->category == CATEGORY::GROUND) //Get Brick vao gird
					{
						cell[i][j][k]->inGrid = true;
						listMapObj.push_back(cell[i][j][k]);
					}
					else if (cell[i][j][k]->category == CATEGORY::ENEMY)
					{
						cell[i][j][k]->inGrid = true;
						listEnemy.push_back(cell[i][j][k]);
					}
				}
			}
		}
	}
}


void Grid::ClearGrid() // Clear Grid
{
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
			cell[i][j].clear();
}
