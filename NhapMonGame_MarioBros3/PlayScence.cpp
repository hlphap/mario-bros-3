#pragma once
#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Tail.h"
#include "OneUpEffect.h"
#include "EffectEndScence.h"
#include "Text.h"



using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int typeMap, int typeCamera) :
	CScene(id, filePath, typeMap, typeCamera)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and listMapObj)
	See scene1.txt, scene2.txt for detail format specification
*/


//# type: 0 = Mario, 1 = Brick, 2 = Goomba, 3 = Koopas, 4 = Flower, 5 = Ground, 6 = ColorBox, 7 = Pipe, 
//8 = QuestionBrick, 9 = WeakBreak, 10 = CloundBrick, 11 = Item, 12 = Bullet


void CPlayScene::TransformDarkScreen()
{
	LPDIRECT3DTEXTURE9 darken = CTextures::GetInstance()->Get(998);
	float l = CGame::GetInstance()->GetCamPosX();
	float t = CGame::GetInstance()->GetCamPosY();


	int alpha = 0;
	DWORD timer = GetTickCount() - timeStartScreenDark;

	if (timer > 1000) alpha = 255;
	else if (timer > 450) alpha = 200;
	else if (timer > 400) alpha = 150;
	else if (timer > 350) alpha = 100;
	else if (timer > 300) alpha = 50;
	CGame::GetInstance()->Draw(l, t, darken, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, alpha);
}

void CPlayScene::TransformLightScreen()
{
	LPDIRECT3DTEXTURE9 darken = CTextures::GetInstance()->Get(998);
	float l = CGame::GetInstance()->GetCamPosX();
	float t = CGame::GetInstance()->GetCamPosY();

	int alpha = 255;
	DWORD timer = GetTickCount() - timeStartScreenLight;

	if (timer > 500) alpha = 0;
	else if (timer > 450) alpha = 50;
	else if (timer > 400) alpha = 100;
	else if (timer > 350) alpha = 150;
	else if (timer > 300) alpha = 200;
	CGame::GetInstance()->Draw(l, t, darken, 0, 0 ,SCREEN_WIDTH, SCREEN_HEIGHT, alpha);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time 

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
//	DebugOut(L"\nAdd IDAni:", ani_id);
	for (size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	CAnimations::GetInstance()->Add(ani_id, ani);
	
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (size_t i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}
void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);
	
	if (tokens.size() < 9) return;
	int id = atoi(tokens[0].c_str());
	wstring file_path_texture = ToWSTR(tokens[1].c_str());
	wstring file_path_data = ToWSTR(tokens[2].c_str());
	
	int numrow_texture = atoi(tokens[3].c_str());
	int numcol_texture = atoi(tokens[4].c_str());
	int numrow_data = atoi(tokens[5].c_str());
	int numcol_data = atoi(tokens[6].c_str());
	int tile_width = atoi(tokens[7].c_str());
	int tile_height = atoi(tokens[8].c_str());
	map = new TileMap();
	map->ID = id;
	map->file_path_data = file_path_data.c_str();
	map->file_path_texture = file_path_texture.c_str();
	map->col_text = numcol_texture;
	map->row_text = numrow_texture;
	map->col_tilemap = numcol_data;
	map->row_tilemap = numrow_data;
	map->tile_width = tile_width;
	map->tile_height = tile_height;
	map->LoadTileMap();
	//Load Camera // Load Board Game
	board = new CScoreBoard(player);
	if (typeMap == 1)
		player->SetOnMap(true);
	else
		player->SetOnMap(false);
	cam = new Camera(player, typeCamera);
	cam->mapW = map->GetWeightMap();
	cam->mapH = map->GetHeightMap();
	grid = new Grid(cam);
	grid->mapW = map->GetWeightMap();
	grid->mapH = map->GetHeightMap();
	map->LoadMap(grid);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	
	
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		
		player = CMario::GetInstance();
		player->SetPosition(x, y);
		player->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		break;
	}
	case OBJECT_TYPE_NUMBER3_EFFECT:
	{
		obj = new CNumber3();
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_BACKGROUND_INTRO:
	{
		obj = new CBackGroundIntro();
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		BackGroundIntro = obj;
		listMapObj_S.push_back(obj);
		break;
	}
	case OBJECT_TYPE_NEW_GAME:
	{
		obj = new CNewGame();
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		newGame = obj;
		listMapObj_S.push_back(obj);
		break;
	}
	/*case OBJECT_TYPE_GOOMBA:
	{
		int type = atoi(tokens[4].c_str());
		int level = atoi(tokens[5].c_str());
		obj = new CGoomba(player, type, level);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);

		listEnemies_S.push_back(obj);
		break;
	}*/
	//case OBJECT_TYPE_BRICK: //Oker
	//	obj = new CBrick();
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	//case OBJECT_TYPE_WEAK_BRICK:	//Oker
	//{
	//	int type = atoi(tokens[6].c_str());
	//	obj = new CWeakBrick(x,y,type);
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	//}
	//case OBJECT_TYPE_CLOUD_BRICK:	 //Oker
	//	obj = new CCloudBrick();
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	//case OBJECT_TYPE_GROUND: // Oker
	//	obj = new CGround();
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	//case OBJECT_TYPE_COLORBOX: // Oker
	//	obj = new CColorBox();
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	case OBJECT_TYPE_PIPE: //Oker
	{
		bool special = atoi(tokens[6].c_str());
		bool where = atoi(tokens[7].c_str());
		bool uses = atoi(tokens[8].c_str());
		int height = atoi(tokens[9].c_str());
		obj = new CPipe(special, where, uses, height);
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listPipe.push_back(obj);
		listMapObj_S.push_back(obj);
		break;
	}
	//case OBJECT_TYPE_FLOWER: //Oker
	//{
	//	int type = atoi(tokens[4].c_str());
	//	obj = new CFlower(player, type);
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listEnemies_S.push_back(obj);
	//	break;
	//}
	/*case OBJECT_TYPE_BOMERANGBROTHER:
	{
		obj = new CBomerangBrother(x, y);
	
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listEnemies_S.push_back(obj);
		break;
	}*/
	case OBJECT_TYPE_SELECT_EFFECT:
	{
		obj = new CSelectionEffect(player,x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listEffect.push_back(obj);
		break;
	}
	//case OBJECT_TYPE_QUESTIONBRICK: //);Oke
	//{
	//	int type = atoi(tokens[6].c_str());
	//	obj = new CQuestionBrick(y,type);
	//	obj->amountX = atoi(tokens[4].c_str());
	//	obj->amountY = atoi(tokens[5].c_str());
	//	
	//	obj->SetPosition(x, y);
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listMapObj_S.push_back(obj);
	//	break;
	//}
	/*case OBJECT_TYPE_COIN_SPIN:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CCoin(x, y, type);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listItems.push_back(obj);
		break;
	}*/
	//case OBJECT_TYPE_ITEM_ENDSCENCE:
	//{
	//	obj = new CItemEndScence(x, y);
	//	posTextX = x - 38;
	//	posTextY = y - 76;
	//	obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	//	listItems_Idle.push_back(obj);
	//	//grid->PushObjToGrid()
	//	break;
	//}
	/*case OBJECT_TYPE_KOOPAS:
		{
			int type = atoi(tokens[4].c_str());
			int level = atoi(tokens[5].c_str());
			obj = new CKoopas(player, x, y, type, level);
			obj->SetPosition(x, y);
			obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
			listEnemies_S.push_back(obj);
		}
		break;*/
	case OBJECT_TYPE_TREE:
	{
		obj = new CTree();
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj_S.push_back(obj);
	}
	break;
	case OBJECT_TYPE_PITSTOP:
	{
		int isLeft = atoi(tokens[4].c_str());
		int isRight = atoi(tokens[5].c_str());
		int isUp = atoi(tokens[6].c_str());
		int isDown = atoi(tokens[7].c_str());
		obj = new CPitStop(isLeft,isRight,isUp,isDown);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listPortal.push_back(obj);
	}
	break;
	/*case OBJECT_TYPE_MOVING_WOOD:
	{
		obj = new CMovingWood();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj_S.push_back(obj);
	}
	break;*/
	case OBJECT_TYPE_PORTAL:
	{
		bool isLeft = atoi(tokens[6].c_str());
		bool isRight = atoi(tokens[7].c_str());
		bool isUp = atoi(tokens[8].c_str());
		bool isDown = atoi(tokens[9].c_str());
		int scene_id = atoi(tokens[10].c_str());
		obj = new CPortal(isLeft,isRight,isUp,isDown,scene_id);
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listPortal.push_back(obj);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
}


void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	//LPCWSTR
	
	ifstream f;
	f.open(sceneFilePath);

	if (f.fail())
	{
		DebugOut(L"Load Sence failed");
		return;
	}
	else
	{
		// current resource section flag
		int section = SCENE_SECTION_UNKNOWN;

		char str[MAX_SCENE_LINE];
		while (f.getline(str, MAX_SCENE_LINE))
		{
			string line(str);

			if (line[0] == '#') continue;	// skip comment lines	

			if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
			if (line == "[SPRITES]") {
				section = SCENE_SECTION_SPRITES; continue;
			}
			if (line == "[ANIMATIONS]") {
				section = SCENE_SECTION_ANIMATIONS; continue;
			}
			if (line == "[ANIMATION_SETS]") {
				section = SCENE_SECTION_ANIMATION_SETS; continue;
			}
			if (line == "[OBJECTS]") {
				section = SCENE_SECTION_OBJECTS; continue;
			}
			if (line == "[TILEMAP]")
			{
				section = SCENE_SECTION_TILEMAP;
				continue;
			}
			if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

			//
			// data section
			//
			switch (section)
			{
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_TILEMAP:	_ParseSection_TILEMAP(line); break;
			}
		}

		f.close();
		
		CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

		
	}
}

void CPlayScene::GetObjInGrid()
{
	listMapObj.clear();
	listEnemies.clear();
	listItems_Idle.clear();
	grid->GetListObj(listMapObj, listEnemies, listItems_Idle);
	for (size_t i = 0; i < listPipe.size(); i++)
	{
		listMapObj.push_back(listPipe[i]);
	}
	//DebugOut(L"\nlistEnenmy size : %d", listItems_Idle.size());


}
void CPlayScene::Update(DWORD dt)
{
//	DebugOut(L"isd %d", id);
	
	if (typeMap == WORLD)
	{
		for (size_t i = 0; i < listEnemies.size(); i++)
		{
			listEnemies[i]->inGrid = false;
		}
		for (size_t i = 0; i < listMapObj.size(); i++)
		{
			listMapObj[i]->inGrid = false;
		}
		for (size_t i = 0; i < listItems_Idle.size(); i++)
		{
			listItems_Idle[i]->inGrid = false;
		}
		GetObjInGrid();
	}
	else
	{
		listMapObj.clear();
		for (size_t i = 0; i < listMapObj_S.size(); i++)
		{
			listMapObj.push_back(listMapObj_S[i]);
		}
	}
//	DebugOut(L"\nListEnemy: %d", listEnemies.size());
//	DebugOut(L"\ListMapObj: %d", listMapObj.size());

	//Update playscence chay truong nen isAttack chua kip ve false thi ben nay da ban dan r
	//FireAttack
#pragma region FireAttack
	if (player->isAttacking
		&& player->level == MARIO_LEVEL_BIG_FIRE
		&& ((!player->isOnAir && GetTickCount() - player->timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_GROUND)
			|| (player->isOnAir && GetTickCount() - player->timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_AIR)))
	{
		if (listBullet.size() < BULLET_AMOUNT) {
			listBullet.push_back(player->bullet);
		}
	}
	if (listBullet.size() == BULLET_AMOUNT)
		player->isAttacking = false;
#pragma endregion

#pragma region TurnOffLight When Go HideMap
	//1.Off Light
	if (player->GetState() == MARIO_STATE_GO_HIDDEN_MAP)
	{
		if (player->y > player->posY_of_PipeIn&& player->isInMainMap)
		{
			timeStartScreenLight = TIME_DEFAULT;
			isScreenDark = true;
			if (timeStartScreenDark == TIME_DEFAULT)
				timeStartScreenDark = GetTickCount();
		}
	}
	if (player->GetState() == MARIO_STATE_GO_MAIN_MAP)
	{
		if (player->y < player->posY_of_PipeIn + 16 && !player->isInMainMap)
		{
			timeStartScreenLight = TIME_DEFAULT;
			isScreenDark = true;
			if (timeStartScreenDark == TIME_DEFAULT)
				timeStartScreenDark = GetTickCount();
		}
	}
	//2.Go HideMap, Find posision go to 
	if (isScreenDark)
	{
		if (player->isInMainMap)
		{
			for (size_t i = 0; i < listPipe.size(); i++)
			{
				CPipe* pipe = dynamic_cast<CPipe*>(listPipe[i]);
				if (pipe->isSpecial & !pipe->isPullMario && !pipe->isInMainMap && player->GetState() == MARIO_STATE_GO_HIDDEN_MAP)
				{
					if (GetTickCount() - timeStartScreenDark > 500)
					{
						player->SetPosition(pipe->x + 4, pipe->y - 16); // SetPosition To Mario Go HideMap
						player->isInMainMap = false;
						player->Fall();
						isScreenDark = false; // Khong tat den nua
						timeStartScreenDark = TIME_DEFAULT;
						if (timeStartScreenLight == TIME_DEFAULT)
						{
							timeStartScreenLight = GetTickCount();
						}
						isFindPipe = true;
					}
				}
			}
			if (isFindPipe == false)
			{
				for (size_t i = 0; i < listPipe.size(); i++)
				{
					CPipe* pipe = dynamic_cast<CPipe*>(listPipe[i]);
					if (!pipe->isPullMario && pipe->isSpecial && pipe->isInMainMap) //Non Pull Mario -> Push Mario
					{
						if (GetTickCount() - timeStartScreenDark > 500)
						{
							player->SetState(MARIO_STATE_GO_MAIN_MAP);
							player->posY_of_PipeOut = pipe->y;
							player->isSlideOutPipe = true;
							player->SetPosition(pipe->x + 4, pipe->y - 17); // SetPosition To Mario Go HideMap
							player->isInMainMap = true;

							isScreenDark = false; // Khong tat den nua
							timeStartScreenDark = TIME_DEFAULT;

							if (timeStartScreenLight == TIME_DEFAULT)
							{
								timeStartScreenLight = GetTickCount();
							}
							isFindPipe = true;
							cam->SetCamPosX(2048.0f);
						}
					}
				}
			}

			
		}

		if (!player->isInMainMap)
		{
			for (size_t i = 0; i < listPipe.size(); i++)
			{
				CPipe* pipe = dynamic_cast<CPipe*>(listPipe[i]);
				if (!pipe->isPullMario && pipe->isSpecial && pipe->isInMainMap && player->GetState() == MARIO_STATE_GO_MAIN_MAP) //Non Pull Mario -> Push Mario
				{
					if (GetTickCount() - timeStartScreenDark > 500)
					{
						player->posY_of_PipeOut = pipe->y;
						player->isSlideOutPipe = true;
						player->SetPosition(pipe->x + 4, pipe->y - 17); // SetPosition To Mario Go HideMap
						player->isInMainMap = true;

						isScreenDark = false; // Khong tat den nua
						timeStartScreenDark = TIME_DEFAULT;

						if (timeStartScreenLight == TIME_DEFAULT)
						{
							timeStartScreenLight = GetTickCount();
						}
					}
				}
			}
		}


	}
#pragma endregion
	
#pragma region Update Obj
	//Update player
	player->Update(dt, &listMapObj, &listEnemies, &listItems, &listItems_Idle, &listEffect, &listPortal, &listFireBall);

	//Update listMapObj
	for (size_t i = 0; i < listMapObj.size(); i++) //MapObj tao ra item
	{
		if (listMapObj[i]->isActive)
		{
				listMapObj[i]->Update(dt, &listItems);
				if (listMapObj[i]->type == TYPE::NEWGAME)
				{
					if (listMapObj[i]->y + 187 < 0)
					{
						BackGroundIntro->isActive = false;
						newGame->isActive = false;
						CLeafTree* leaf = new CLeafTree(120,-16);
						listItems.push_back(leaf);
						//Create 
					}
				}
		}
		else
		{
			listMapObj.erase(listMapObj.begin() + i);
		}
	}
	//Update listEnemy
	for (size_t i = 0; i < listEnemies.size(); i++)
	{
		if (listEnemies[i]->isActive)
		{
				listEnemies[i]->Update(dt, &listMapObj);
				if (listEnemies[i]->type == TYPE::KOOPAS)
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(listEnemies[i]);
					koopas->IsCollisionWhenShellMove(&listMapObj, &listEnemies, &listEffect);

				}
				if (listEnemies[i]->type == TYPE::FLOWER)
				{
					CFlower* flower = dynamic_cast<CFlower*>(listEnemies[i]);
					flower->CreateFireBall(&listFireBall);
				}
				if (listEnemies[i]->type == TYPE::BOOMERANG_BROTHER)
				{
					CBomerangBrother* brother = dynamic_cast<CBomerangBrother*>(listEnemies[i]);
					brother->CreateBoomerang(&listFireBall);
				}
		}
		else
			listEnemies.erase(listEnemies.begin() + i);
	}
	//Update listBullet
	for (UINT i = 0; i < listBullet.size(); i++) {
		if (listBullet[i] != NULL)
		{
			if (listBullet[i]->isActive)
			{
				if (listBullet[i]->isCheckInCamera())
					listBullet[i]->Update(dt, &listMapObj, &listEnemies, &listEffect);
				else
					listBullet.erase(listBullet.begin() + i);
			}
			else
				listBullet.erase(listBullet.begin() + i);
		}
	}

	//Update listFireBall
	for (UINT i = 0; i < listFireBall.size(); i++) {

		if (listFireBall[i]->isActive)
		{
			if (listFireBall[i]->isCheckInCamera())
				listFireBall[i]->Update(dt, &listMapObj);
			else
				listFireBall.erase(listFireBall.begin() + i);
		}
		else
			listFireBall.erase(listFireBall.begin() + i);
	}
	for (size_t i = 0; i < listItems.size(); i++)
	{
		if (listItems[i]->isActive)
		{
			if (listItems[i]->isCheckInCamera())
			{
				listItems[i]->Update(dt, &listMapObj);
				//When Press P Switch Tranform To WeakBrick
				if (listItems[i]->type == TYPE::SWITCH_P)
				{
					if (listItems[i]->GetState() == SWITCH_P_STATE_PRESSED)
					{
						CSwitch_P* switchP = dynamic_cast<CSwitch_P*>(listItems[i]);
						if (!switchP->isTransformed)
						{
							switchP->TranFormationBrick(&listMapObj, &listItems);
							switchP->isTransformed = true;
						}
					}
				}
				//Ready Tranform Coin Idle to WeakBrick
				if (listItems[i]->type == TYPE::COIN_IDLE_STATIC)
				{
					if (listItems[i]->GetState() == COIN_IDLE_STATIC_TRANFORM_TO_WEAKBRICK)
					{
						CCoin* coin = dynamic_cast<CCoin*>(listItems[i]);
						coin->isActive = false;
						CWeakBrick * weakBrick = new CWeakBrick(coin->x, coin->y, 0);
						weakBrick->SetPosition(coin->x - 4, coin->y);
						weakBrick->inGrid = false;
						float l, t, r, b;
						weakBrick->GetBoundingBox(l, t, r, b);
						weakBrick->CreatePosGrid(l, t, r, b);
						grid->PushObjToGrid(weakBrick);
					}
				}
			}
		}
		else
		{
			//Khi Item đc dùng thì tạo Effect
			CScoreEffect* scoreEffect = new CScoreEffect(listItems[i]->x, listItems[i]->y);
			if (listItems[i]->type == TYPE::COIN_EFFECT)
			{
				player->changeScore = true;
				player->score = 100;
				scoreEffect->SetScore(100);
				listEffect.push_back(scoreEffect);
			}
			else
				if (listItems[i]->type == TYPE::LEAF_TREE)
				{
					player->changeScore = true;
					player->score = 1000;
					scoreEffect->SetScore(1000);
					listEffect.push_back(scoreEffect);
				}
				else
					if (listItems[i]->type == TYPE::MUSHROOM)
					{
						CMushroom* mushroom = dynamic_cast<CMushroom*>(listItems[i]);
						if (mushroom->color == MUSHROOM_RED)
						{
							player->changeScore = true;
							player->score = 1000;
							scoreEffect->SetScore(1000);
							listEffect.push_back(scoreEffect);
						}
						else if (mushroom->color == MUSHROOM_GREEN)
						{
							COneUpEffect* effect = new COneUpEffect(player->x, player->y);
							listEffect.push_back(effect);
						}

					}
					else
						if (listItems[i]->type == TYPE::COIN_IDLE_STATIC || listItems[i]->type == TYPE::COIN_IDLE_SPIN)
						{
							player->changeScore = true;
							player->score = 50;
						}
						else
							if (listItems[i]->type == TYPE::ITEM_END_GAME)
							{
								CEffectEndScence* effect = new CEffectEndScence(listItems[i]->x, listItems[i]->y);
								srand(time(NULL));
								effect->typeEffect = 1 + rand() % (3 + 1 - 1);
								listEffect.push_back(effect);
							}
			listItems.erase(listItems.begin() + i);
		}
	}
	for (size_t i = 0; i < listItems_Idle.size(); i++)
	{
		if (listItems_Idle[i]->isActive)
		{
			listItems_Idle[i]->Update(dt, &listMapObj);
		}
		else
		{
				if (listItems_Idle[i]->type == TYPE::COIN_IDLE_STATIC || listItems_Idle[i]->type == TYPE::COIN_IDLE_SPIN)
				{
					player->changeScore = true;
					player->score = 50;
				}
				else
					if (listItems_Idle[i]->type == TYPE::ITEM_END_GAME)
					{
						CItemEndScence* item = dynamic_cast<CItemEndScence*>(listItems_Idle[i]);
						posTextX = item->posTextX;
						posTextY = item->posTextY;
						CEffectEndScence* effect = new CEffectEndScence(listItems_Idle[i]->x, listItems_Idle[i]->y);
						srand(time(NULL));
						effect->typeEffect = 1 + rand() % (3 + 1 - 1);
						listEffect.push_back(effect);
					}
			listItems_Idle.erase(listItems_Idle.begin() + i);
		}
	}
	//Update list Effect
	for (size_t i = 0; i < listEffect.size(); i++)
	{
		if (listEffect[i]->isActive)
			listEffect[i]->Update(dt, &listMapObj);
		else
			listEffect.erase(listEffect.begin() + i);
	}

	//Update list Text
	for (size_t i = 0; i < listText.size(); i++)
	{
		listText[i]->Update(dt);
	}

	cam->Update(dt);
	map->Update();
	//if (typeMap == WORLD)
		board->Update(dt, cam);

	if (player == NULL) return;
#pragma endregion

#pragma region EndScene
	if (player->isCompleteScene && !isCreatedText)
	{
		if (timeStartEndScence == TIME_DEFAULT)
		{
			timeStartEndScence = GetTickCount();
			//CText* text1 = new CText(2650, 260, "COURSE CLEAR");
			DebugOut(L"posX: %f%f", posTextX, posTextY);
			CText* text1 = new CText(posTextX, posTextY, "COURSE CLEAR");
			listText.push_back(text1);
		}
		if (GetTickCount() - timeStartEndScence > 500 && timeStartEndScence != TIME_DEFAULT)
		{
			CText* text2 = new CText(posTextX - 6, posTextY + 20, "YOU GOT A CARD");
			listText.push_back(text2);
			isCreatedText = true;
		}
	}
	if (GetTickCount() - timeStartEndScence > 2000 && timeStartEndScence != TIME_DEFAULT)
	{
		timeStartEndScence = TIME_DEFAULT;
	}
	else
		if (player->isCompleteScene && isCreatedText && timeStartEndScence == TIME_DEFAULT)
		{
			//Return Selection Map
			CGame::GetInstance()->SwitchScene(player->portalReturn->GetSceneId());
			player->SetPosition(player->portalPre->x, player->portalPre->y);
			player->isGoEndScene = false;
			player->isSelectMap = true;
			isCreatedText = false;
			player->isCompleteScene = false;
		}
#pragma endregion
	if (typeMap == WORLD)
	{
		grid->UpdateGrid();
	}
}	

void CPlayScene::Render()
{
	map->Draw();
	for (size_t i = 0; i < listEnemies.size(); i++)
	{
		listEnemies[i]->Render();
	}
	player->Render();
	for (size_t i = 0; i < listMapObj.size(); i++)
	{
		listMapObj[i]->Render();
	}
	for (size_t i = 0; i < listItems.size(); i++)
	{
		listItems[i]->Render();
	}
	for (size_t i = 0; i < listItems_Idle.size(); i++)
	{
		listItems_Idle[i]->Render();
	}
	
	for (UINT i = 0; i < listBullet.size(); i++) {

		if (listBullet[i] != NULL)
		listBullet[i]->Render();
	}	

	for (UINT i = 0; i < listFireBall.size(); i++) {

		if (listFireBall[i] != NULL)
			listFireBall[i]->Render();
	}
	
	for (UINT i = 0; i < listEffect.size(); i++) {

		if (listEffect[i] != NULL)
			listEffect[i]->Render();
	}
	
	for (UINT i = 0; i < listPortal.size(); i++)
	{
		listPortal[i]->Render();
	}


	if (isScreenDark)
	{
		TransformDarkScreen();
	}
	else
	{
		TransformLightScreen();	
	}
		
	for (size_t i = 0; i < listText.size(); i++)
	{
		listText[i]->Render();
	}
	if (!player->isIntroScene)
		board->Render();
	
	CTail::GetInstance()->Render();
		
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (size_t i = 0; i < listMapObj.size(); i++)
		delete listMapObj[i];

	listMapObj_S.clear();
	listEnemies_S.clear();
	listMapObj.clear();
	listText.clear();
	listBullet.clear();
	listEffect.clear();
	listPortal.clear();
	listPipe.clear();
	listEnemies.clear();
	listItems.clear();
	listFireBall.clear();

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}





void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->isGoEndScene || mario->isGoingSelectMap)
		return;
	switch (scence->typeMap)
	{
	case TYPEMAP::WORLD:
		{
		if (mario->GetState() == MARIO_STATE_DIE) return;
			if (mario->isGoHidenMap) return;
			switch (KeyCode)
			{
			case DIK_Q:
				mario->isHoldingShell = true;
				break;
			case DIK_S:
				if (!mario->isOnAir)
				{
					mario->Jump();
				}
				break;
			case DIK_A:
				if (!mario->isAttacking)
				{
					mario->Attack();
				}
				break;
			case DIK_R:
				mario->Reset();
				break;
			case DIK_1:
				mario->SetLevel(MARIO_LEVEL_SMALL);
				//mario->SetPosition(mario->x, 0);
				break;
			case DIK_2:
				mario->SetLevel(MARIO_LEVEL_BIG);
				//mario->SetPosition(mario->x, 0);
				break;
			case DIK_3:
				mario->SetLevel(MARIO_LEVEL_BIG_TAIL);
				//mario->SetPosition(mario->x, 0);
				break;
			case DIK_4:
				mario->SetLevel(MARIO_LEVEL_BIG_FIRE);
				//mario->SetPosition(mario->x, 0);
				break;
			case DIK_T:
				mario->SetPosition(mario->x, 0);
				break;
			}
			break;
		}
	case TYPEMAP::WORLDMAP:
		{
			switch (KeyCode)
			{
			case DIK_Q:
			{
				mario->isLocationSelect = !mario->isLocationSelect;
				break;
			}			
			case DIK_RIGHT:
			{
				if (mario->isAllowRight)
				{
					mario->directSelectMap = DIRECT_RIGHT;
					mario->GoSelectMap();
				}
				break;
			}
			case DIK_LEFT:
			{
				if (mario->isAllowLeft)
				{
					mario->directSelectMap = DIRECT_LEFT;
					mario->GoSelectMap();
				}
				break;
			}
			case DIK_UP:
				if (mario->isAllowUp)
				{
					mario->directSelectMap = DIRECT_UP;
					mario->GoSelectMap();
				}
				break;
			case DIK_DOWN:
				if (mario->isAllowDown)
				{
					mario->directSelectMap = DIRECT_DOWN;
					mario->GoSelectMap();
				}
				break;
			case DIK_S:
				mario->isPressKeyDown = true;
				if (mario->isIntroScene)
				{
					CGame::GetInstance()->SwitchScene(1);
					mario->isIntroScene = false;
				}
			}
			break;
		}
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->isGoEndScene)
		return;
	switch (scence->typeMap)
	{
	case TYPEMAP::WORLD:
	{
		if (mario->GetState() == MARIO_STATE_DIE) return;
		if (mario->isGoHidenMap) return;
		switch (KeyCode)
		{
		case DIK_Q:
			mario->isHoldingShell = false;
			break;
		case DIK_A:
			//Cập nhật nhả cờ
			mario->isSpeedUp = false;
			mario->isKeepHoldShell = false;
			mario->isHoldingShell = false;
			break;
		case DIK_S:
			//DebugOut(L"\nKeepJump: %d", player->isKeepJump);
			if (mario->isFalling && mario->isKeepJump)
			{
				if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->isOnAir)
				{
					mario->KeepJump();
					break;
				}
			}
			mario->Fall();
			break;
		}
		break;
	}
	case TYPEMAP::WORLDMAP:
		{
			switch (KeyCode)
			{
			case DIK_S:
				mario->isPressKeyDown = false;
				break;
			}
			break;
		}
	}
	
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	if (mario->isGoEndScene)
		return;
	switch (scence->typeMap)
	{
	case TYPEMAP::WORLD:
	{
		//Mario Die
		if (mario->GetState() == MARIO_STATE_DIE) return;
		if (mario->isGoHidenMap) return;

		//Control
		if (game->IsKeyDown(DIK_A))
		{
			//Khong giam toc do
			mario->SpeedUp();
			mario->HoldShell();
		}

		//Mario Go Right
		if (game->IsKeyDown(DIK_RIGHT))
		{
			//(L"\nvx: %f", player->vx);
			if ((mario->nx * mario->vx < 0) && (!mario->GetJump()) && (mario->Getvx() < -MARIO_SPEED_CAN_STOP))
			{
				mario->Stop();
			}
			mario->Right();
			mario->Go();
		}
		//Mario Go Left
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if ((mario->nx * mario->vx < 0) && (!mario->GetJump()) && (mario->Getvx() > MARIO_SPEED_CAN_STOP))
			{
				mario->Stop();
			}
			mario->Left();
			mario->Go();
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (!mario->isOnAir)
				mario->Sit();
		}
		// Mario Idle
		else
			mario->Idle();
	}
	case TYPEMAP::WORLDMAP:
	{
		break;
	}

	}

}