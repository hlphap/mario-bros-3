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
	Load scene resources from scene file (textures, sprites, animations and objects)
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
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
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

	//int nx = atoi(tokens[4].c_str());
	//int ny = atoi(tokens[5].c_str());
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
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: //Oker
		obj = new CBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_WEAK_BRICK:	//Oker
		obj = new CWeakBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_CLOUD_BRICK:	 //Oker
		obj = new CCloudBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_GROUND: // Oker
		obj = new CGround();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_COLORBOX: // Oker
		obj = new CColorBox();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_PIPE: //Oker
		obj = new CPipe();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_FLOWER: //Oker
		obj = new CFlower();
		obj->state = OBJECT_TYPE_FLOWER;
		break;
	case OBJECT_TYPE_QUESTIONBRICK: //Oke
		obj = new CQuestionBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(player); break;
	
	//case OBJECT_TYPE_BOUNDARYBRICK:
	/*	obj = new CBoundaryBrick();
		obj->amountX = atoi(tokens[4].c_str());
		obj->amountY = atoi(tokens[5].c_str());
		break;*/
		//break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_TileMap(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 9) return;
	int ID = atoi(tokens[0].c_str());
	wstring file_texture = ToWSTR(tokens[1]);
	wstring file_path = ToWSTR(tokens[2]);

	int row_on_textures = atoi(tokens[3].c_str());
	int col_on_textures = atoi(tokens[4].c_str());
	int row_on_tile_map = atoi(tokens[5].c_str());
	int col_on_tile_map = atoi(tokens[6].c_str());
	int tile_width = atoi(tokens[7].c_str());
	int tile_height = atoi(tokens[8].c_str());
	//int texID = atoi(tokens[0].c_str());
	map = new TileMap(ID, file_texture.c_str(), file_path.c_str(), row_on_textures, col_on_textures, row_on_tile_map, col_on_tile_map, tile_width, tile_height);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

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
			if (line == "[TILEMAP]") {
				section = SCENE_SECTION_TILEMAP; continue;
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
			case SCENE_SECTION_TILEMAP: _ParseSection_TileMap(line); break;
			}
		}

		f.close();

		CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

		DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	}
	
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	
	//Update playscence chay truong nen isAttack chua kip ve false thi ben nay da ban dan r
	if (player->isAttacking 
		&&  player->level == MARIO_LEVEL_BIG_FIRE
		&& ((!player->isOnAir && GetTickCount() - player->timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_GROUND)
			|| (player->isOnAir && GetTickCount() - player->timeStartAttack >= MARIO_TIME_BIG_FIRE_ATTACK_ON_AIR)))
	{
		CBullet* bullet = new CBullet();
		bullet->timer = GetTickCount();
		if (player->nx == 1)
		{
			bullet->SetPosition(player->x + MARIO_BIG_BBOX_WIDTH, player->y + MARIO_D_HEED_TO_HAND_ATTACK);
			bullet->nx = 1;
			bullet->SetState(BULLET_STATE_FLY_RIGHT);
		} 
		else if (player->nx == -1)
		{
			bullet->SetPosition(player->x,player->y + MARIO_D_HEED_TO_HAND_ATTACK);	
			bullet->nx = -1;
			bullet->SetState(BULLET_STATE_FLY_LEFT);
		}
		if (bullets.size() < BULLET_AMOUNT) {
			bullets.push_back(bullet);
		}
	}
	if (bullets.size() == BULLET_AMOUNT)
		player->isAttacking = false;


	if (player->isAttacking
		&& player->level == MARIO_LEVEL_BIG_TAIL)
	{
		if (tail->timer == TIME_DEFAUL) tail->timer = GetTickCount();
		if (player->nx == 1)
		{
			tail->SetPosition(player->x + MARIO_BIG_BBOX_WIDTH, player->y + MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->nx = 1;
			tail->SetState(TAIL_CAN_KILL);
		}
		else if (player->nx == -1)
		{
			tail->SetPosition(player->x, player->y + MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->nx = -1;
			tail->SetState(TAIL_CAN_KILL);
		}
	}
	else if (player->level == MARIO_LEVEL_BIG_TAIL)/*if (GetTickCount() - tail->timer >= 375 && tail->timer != TIME_DEFAUL)*/
	{
		tail->timer = TIME_DEFAUL;
		if (player->nx == 1)
		{
			//DebugOut(L"Im heare");
			tail->SetPosition(player->x, player->y + MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->nx = 1;
			tail->SetState(TAIL_CANNOT_KILL);
		}
		else if (player->nx == -1)
		{
			tail->SetPosition(player->x + MARIO_BIG_BBOX_WIDTH, player->y+ MARIO_D_HEED_TO_TAIL_ATTACK);
			tail->nx = -1;
			tail->SetState(TAIL_CANNOT_KILL);
		}
	}
	
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < bullets.size(); i++) {
		
		bullets[i]->Update(dt, &coObjects);
	}
	tail->Update(dt ,&coObjects);
	//DebugOut(L"\nSize Truoc Xoa Bullet: %d", bullets.size());
	DeleteBullet();
	//DebugOut(L"\nSize Bullet: %d", bullets.size());


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;

	CGame::GetInstance()->cam_y = 150;
	if (player->x > (SCREEN_WIDTH / 2) && player->x + (SCREEN_WIDTH / 2) < map->GetWidthTileMap())
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		CGame::GetInstance()->cam_x = cx;
	}
}

void CPlayScene::Render()
{
	map->Draw();
	for (int i = objects.size()-1; i >=0; i--)
		objects[i]->Render();
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}
	tail->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::DeleteBullet()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isExploding)
		{
			if (GetTickCount() - bullets[i]->timeStartColl >= BULLET_TIME_EXPLOSIVE && bullets[i]->timeStartColl != TIME_DEFAUL)
			bullets.erase(bullets.begin() + i);
		}
		else
		if (GetTickCount() - bullets[i]->timer > BULLET_TIME_EXITS)
			bullets.erase(bullets.begin() + i);
	}

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
		mario->isSpeedUp = false;
		mario->isHoldShell = false;
		mario->isHoldingShell = false;
		break;
	case DIK_S:
		//DebugOut(L"\nKeepJump: %d", mario->isKeepJump);
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
	}
	
	//Mario Go Right
	if (game->IsKeyDown(DIK_RIGHT))
	{
		//(L"\nvx: %f", mario->vx);
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