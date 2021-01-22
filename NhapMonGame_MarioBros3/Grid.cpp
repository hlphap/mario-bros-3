#include "Grid.h"
#include "Utils.h"



void Grid::InsertObjToGrid(string line)
{
	CGameObject* obj = CreateNewObj(line);
	if (obj == NULL)
		return;
	else
		PushObjToGrid(obj);
}

CGameObject* Grid::CreateNewObj(string line)
{
	CMario* player = CMario::GetInstance();
	CGameObject *obj = NULL;
	vector<string> tokens = split(line);
	//if (tokens.size() < 3) exit;
	int id = atoi(tokens[0].c_str());
	int object_type = atoi(tokens[1].c_str());
	float x = atof(tokens[2].c_str());
	float y = atof(tokens[3].c_str());
	int ani_set_id = atoi(tokens[4].c_str());
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	int GL, GR, GT, GB;
	switch (object_type)
	{
	case OBJECT_TYPE_GROUND:
		obj = new CGround();
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	case OBJECT_TYPE_CLOUD_BRICK:
		obj = new CCloudBrick();
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	case OBJECT_TYPE_COLORBOX:
		obj = new CColorBox();
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	case OBJECT_TYPE_WEAK_BRICK:
	{
		int type = atoi(tokens[7].c_str());
		obj = new CWeakBrick(x,y,type);
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[8].c_str());
		GT = atoi(tokens[9].c_str());
		GR = atoi(tokens[10].c_str());
		GB = atoi(tokens[11].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}
	case OBJECT_TYPE_QUESTIONBRICK:
	{
		int type = atoi(tokens[7].c_str());
		obj = new CQuestionBrick(y, type);
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[8].c_str());
		GT = atoi(tokens[9].c_str());
		GR = atoi(tokens[10].c_str());
		GB = atoi(tokens[11].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}	
	case OBJECT_TYPE_PIPE:
	{
		bool special = atoi(tokens[7].c_str());
		bool where = atoi(tokens[8].c_str());
		bool uses = atoi(tokens[9].c_str());
		int height = atoi(tokens[10].c_str());
		obj = new CPipe(special, where, uses, height);
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[11].c_str());
		GT = atoi(tokens[12].c_str());
		GR = atoi(tokens[13].c_str());
		GB = atoi(tokens[14].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}
	case OBJECT_TYPE_MOVING_WOOD:
	{
		obj = new CMovingWood();
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}
	case OBJECT_TYPE_GOOMBA:
	{
		int type = atoi(tokens[7].c_str());
		int level = atoi(tokens[8].c_str());
		obj = new CGoomba(player,type,level);
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[9].c_str());
		GT = atoi(tokens[10].c_str());
		GR = atoi(tokens[11].c_str());
		GB = atoi(tokens[12].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		listEnemy_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_KOOPAS:
	{
		int type = atoi(tokens[7].c_str());
		int level = atoi(tokens[8].c_str());
		obj = new CKoopas(player, x, y, type, level);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[9].c_str());
		GT = atoi(tokens[10].c_str());
		GR = atoi(tokens[11].c_str());
		GB = atoi(tokens[12].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		listEnemy_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_FLOWER:
	{
		int type = atoi(tokens[7].c_str());
		obj = new CFlower(player, type);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[8].c_str());
		GT = atoi(tokens[9].c_str());
		GR = atoi(tokens[10].c_str());
		GB = atoi(tokens[11].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		listEnemy_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_BOMERANGBROTHER:
	{
		obj = new CBomerangBrother(x,y);
		obj->amountX = atoi(tokens[5].c_str());
		obj->amountY = atoi(tokens[6].c_str());
		//obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		listEnemy_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_COIN_SPIN:
	{
		int type = atoi(tokens[7].c_str());
		obj = new CCoin(x, y, type);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[8].c_str());
		GT = atoi(tokens[9].c_str());
		GR = atoi(tokens[10].c_str());
		GB = atoi(tokens[11].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}
	case OBJECT_TYPE_ITEM_ENDSCENCE:
	{
		obj = new CItemEndScence(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		GL = atoi(tokens[7].c_str());
		GT = atoi(tokens[8].c_str());
		GR = atoi(tokens[9].c_str());
		GB = atoi(tokens[10].c_str());
		obj->SetGridPos(GL, GT, GR, GB);
		break;
	}
	default:
		break;
	}
	return obj;
}

void Grid::PushObjToGrid(CGameObject* obj)
{
	int left;
	int right;
	int top;
	int bot;
	obj->GetGridPos(left, top, right, bot);
	for (int row = top; row <= bot; row++)
	{
		for (int col = left; col <= right; col++)
		{
			if (obj->category == CATEGORY::GROUND || obj->category == CATEGORY::ITEM)
				unMoveObj[row][col].push_back(obj);
			else
				moveObj[row][col].push_back(obj);
		}
	}
}

void Grid::UpdateGrid()
{
	ClearGrid();
	for (int i = 0; i < listEnemy_S.size(); i++)
	{
		float l, t, r, b;
		listEnemy_S[i]->GetBoundingBox(l, t, r, b);
		if (b >= mapH || l < 0 || r > mapW || t < 0)
			listEnemy_S[i]->isActive = false;
		int Top = int(t / cellHeight);
		int Left = int(l / cellWidth);
		int Right = ceil(r / cellWidth);
		int Bottom = ceil(b / cellHeight);
		if (listEnemy_S[i]->isActive)
		{
			for (int row = Top; row <= Bottom; row++)
				for (int col = Left; col <= Right; col++)
				{
					moveObj[row][col].push_back(listEnemy_S[i]);
				}
			listEnemy_S[i]->SetGridPos(Left, Top, Right, Bottom);
		}
	}
}

Grid::Grid(Camera *cam) // Khoi tao Cell, Row Col
{
	this->cam = cam;
	ClearGrid();
}

void Grid::GridResize()
{
	numRow = (mapH + cellHeight) / cellHeight;
	numCol = (mapW + cellWidth) / cellWidth;

	unMoveObj.resize(numRow);
	for (int i = 0; i < numRow; i++)
		unMoveObj[i].resize(numCol);

	moveObj.resize(numRow);
	for (int i = 0; i < numRow; i++)
		moveObj[i].resize(numCol);

}

void Grid::GetListObj(vector<LPGAMEOBJECT>& listMapObj, vector<LPGAMEOBJECT>& listEnemy, vector<LPGAMEOBJECT> &listItem) //Get listMapObj, Get listEnemy on Grid NearCamera
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
			for (int k = 0; k < unMoveObj[i][j].size(); k++)
			{
				if (unMoveObj[i][j][k]->isActive && !unMoveObj[i][j][k]->inGrid)
				{
					if (unMoveObj[i][j][k]->category == CATEGORY::GROUND) //Get UnMoveObj
					{
						unMoveObj[i][j][k]->inGrid = true;
						listMapObj.push_back(unMoveObj[i][j][k]);
					}
					else if (unMoveObj[i][j][k]->category == CATEGORY::ITEM)
					{
						unMoveObj[i][j][k]->inGrid = true;
						listItem.push_back(unMoveObj[i][j][k]);
					}
				}
			}

			for (int k = 0; k < moveObj[i][j].size(); k++)
			{
				if (moveObj[i][j][k]->isActive && !moveObj[i][j][k]->inGrid)
				{
					if (moveObj[i][j][k]->category == CATEGORY::ENEMY)
					{
						moveObj[i][j][k]->inGrid = true;
						listEnemy.push_back(moveObj[i][j][k]);
					}
				}
			}
		}
	}
}

void Grid::ClearGrid() // Clear Grid
{
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			moveObj[i][j].clear();
		}
	}
}
