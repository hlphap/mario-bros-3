#pragma once
#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Tail.h"



using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and listMapObj)
	See scene1.txt, scene2.txt for detail format specification
*/


//# type: 0 = Mario, 1 = Brick, 2 = Goomba, 3 = Koopas, 4 = Flower, 5 = Ground, 6 = ColorBox, 7 = Pipe, 
//8 = QuestionBrick, 9 = WeakBreak, 10 = CloundBrick, 11 = Item, 12 = Bullet


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
	map = TileMap::GetInstance();
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
	map->LoadMap();
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
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		player = (CMario*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		int type = atoi(tokens[4].c_str());
		int level = atoi(tokens[5].c_str());
		obj = new CGoomba(player, type, level);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_BRICK: //Oker
		obj = new CBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_WEAK_BRICK:	//Oker
		obj = new CWeakBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_CLOUD_BRICK:	 //Oker
		obj = new CCloudBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_GROUND: // Oker
		obj = new CGround();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_COLORBOX: // Oker
		obj = new CColorBox();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_PIPE: //Oker
		obj = new CPipe();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	case OBJECT_TYPE_FLOWER: //Oker
	{
		int type = atoi(tokens[4].c_str());
		obj = new CFlower(player, type);
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_QUESTIONBRICK: //);Oke
	{
		int type = atoi(tokens[6].c_str());
		obj = new CQuestionBrick(y,type);
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		
		obj->SetPosition(x, y);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
		break;
	}
	case OBJECT_TYPE_KOOPAS:
		{
			int type = atoi(tokens[4].c_str());
			int level = atoi(tokens[5].c_str());
			obj = new CKoopas(player, type, level);
			obj->SetPosition(x, y);
			obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
			listEnemies.push_back(obj);
		}
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		obj->animation_set = CAnimationSets::GetInstance()->Get(ani_set_id);
		listMapObj.push_back(obj);
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
			case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
			}
		}

		f.close();

		CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		cam = new Camera(player);
		DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	}
	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CKoopas* obj = new CKoopas(player);
	obj->x = 10.0f;
	obj->y = 300.0f;
	obj->SetAnimationSet(animation_sets->Get(4));
	listMapObj.push_back(obj);*/
}

void CPlayScene::Update(DWORD dt)
{
	//Update playscence chay truong nen isAttack chua kip ve false thi ben nay da ban dan r
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



	//Update player
	player->Update(dt, &listMapObj, &listEnemies, &listItems,&listEffect);

	//Update listMapObj
	for (size_t i = 0; i < listMapObj.size(); i++)
	{
		listMapObj[i]->Update(dt, &listItems);
	}
	//Update listItem
	//DebugOut(L"ListItem size: %d \n", listItems.size());
	for (size_t i = 0; i < listItems.size(); i++)
	{
		if (listItems[i]->isActive)
			listItems[i]->Update(dt, &listMapObj);
		else
			listItems.erase(listItems.begin() + i);
	}

	//Update listEnemy
	for (size_t i = 0; i < listEnemies.size(); i++)
	{
		if (listEnemies[i]->isActive)
			listEnemies[i]->Update(dt, &listMapObj);
		else
			listEnemies.erase(listEnemies.begin() + i);
	}
	//Update listBullet
	for (UINT i = 0; i < listBullet.size(); i++) {

		if (listBullet[i]->isActive)
			listBullet[i]->Update(dt, &listMapObj, &listEnemies, &listEffect);
		else
			listBullet.erase(listBullet.begin() + i);
	}

	//Update list Effect
	for (size_t i = 0; i < listEffect.size(); i++)
	{
		if (listEffect[i]->isActive)
			listEffect[i]->Update(dt,&listMapObj);
		else
			listEffect.erase(listEffect.begin() + i);
	}

	

	if (player == NULL) return;

	
	map->Update();
	cam->Update();
}

void CPlayScene::Render()
{
	map->Draw();
	for (size_t i = 0; i < listItems.size(); i++)
	{
		listItems[i]->Render();
	}
	for (size_t i = 0; i < listMapObj.size(); i++)
	{
		listMapObj[i]->Render();
	}
	
	for (size_t i = 0; i < listEnemies.size(); i++)
	{
		listEnemies[i]->Render();
	}

	for (UINT i = 0; i < listBullet.size(); i++) {

		if (listBullet[i] != NULL)
		listBullet[i]->Render();
	}	
	for (UINT i = 0; i < listEffect .size(); i++) {

		if (listEffect[i] != NULL)
			listEffect[i]->Render();
	}
	player->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (size_t i = 0; i < listMapObj.size(); i++)
		delete listMapObj[i];

	listMapObj.clear();
	player = NULL;
	map = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}



void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
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
		mario->SetPosition(mario->x, 0);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(mario->x, 0);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_BIG_TAIL);
		mario->SetPosition(mario->x, 0);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_BIG_FIRE);
		mario->SetPosition(mario->x, 0);
		break;
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_Q:
		mario->isHoldingShell = false;
		break;
	case DIK_A:
		//Cập nhật nhả cờ
		mario->isSpeedUp = false;
		mario->isHoldShell = false;
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
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	//Mario Die
	if (mario->GetState() == MARIO_STATE_DIE) return;


	//Control
	if (game->IsKeyDown(DIK_A))
	{
		mario->SpeedUp();
		mario->HoldShell();
	}
	
	//Mario Go Right
	if (game->IsKeyDown(DIK_RIGHT))
	{
		//(L"\nvx: %f", player->vx);
		if ((mario->nx * mario->vx < 0)&&(!mario->GetJump())&&(mario->Getvx()<-MARIO_SPEED_CAN_STOP))
		{
			mario->Stop();	
		}
			mario->Right();
			mario->Go();
	}
	//Mario Go Left
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if ((mario->nx * mario->vx < 0)&&(!mario->GetJump()) && (mario->Getvx() > MARIO_SPEED_CAN_STOP))
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