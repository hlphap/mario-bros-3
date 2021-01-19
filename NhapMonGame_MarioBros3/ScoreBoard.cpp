#include "ScoreBoard.h"
#include "Utils.h"
#include "Textures.h"

CScoreBoard::CScoreBoard(CMario* mario)
{
	this->mario = mario;
	timeStartPlay = GetTickCount();
	x = floor(CGame::GetInstance()->GetCamPosX()); // round(cam->GetCamPosX());
	y = floor(CGame::GetInstance()->GetCamPosY() + 190.0f);// round(cam->GetCamPosY() + 190.0f);
	//ncountDown = 300;
}


void CScoreBoard::Update(DWORD dt, Camera* cam)
{
	x = floor(CGame::GetInstance()->GetCamPosX()); // round(cam->GetCamPosX());
	y = floor(CGame::GetInstance()->GetCamPosY() + 190.0f);// round(cam->GetCamPosY() + 190.0f);
	
#pragma region Energy
	//Energy
	//Kiem tra toc do mario-> tao Nang luong
	//Mot Nat
	float oneEnergy = (MARIO_RUNNING_MAX_SPEED - MARIO_WALKING_MAX_SPEED) / 6;

	if (mario->isDecreaseSpeed)
	{
		if (GetTickCount() - timeStartDecree > 450)
		{
			numEnergy--;
			timeStartDecree = GetTickCount();
		}
		lastnumEnergy = numEnergy;
	}

	if (mario->isSpeedUp)
	{
		numEnergy = int((abs(mario->vx) - MARIO_WALKING_MAX_SPEED) / oneEnergy);
		if (numEnergy < lastnumEnergy)
			numEnergy = lastnumEnergy;
	}
	if (numEnergy < 0)
	{
		numEnergy = 0; //Phongf truong hop Ep Kieu Loix
	}
	if (mario->isKeepJump_HightFlying)
	{
		numEnergy = 6;
	}
	energy = new CEnergy(numEnergy);
	energy->SetPosition(x + 50, y + 7);
	energy->Update(dt);

	//Tao P
	if (numEnergy == 6)
	{
		pMax = new CP_MaxSpeed();
		pMax->SetPosition(x + 100, y + 7);
		pMax->Update(dt);
	}
	else
		pMax = NULL;
#pragma endregion
#pragma region Total Score
	//Total Score
	if (mario->changeScore)
	{
		totalScore += mario->score;
		mario->changeScore = false;
	}
	numbertotalScore = new CNumber(totalScore,7);
	numbertotalScore->SetPosition(x + 50, y + 15);
	numbertotalScore->Update(dt);
#pragma endregion
#pragma region NumCoin
	//Coin NumCoin
	numCoin = mario->numCoin;
	numberCoin = new CNumber(numCoin,1);
	numberCoin->SetPosition(x + 135, y + 7);
	numberCoin->Update(dt);

#pragma endregion
#pragma region TimeCountDown
	//TimeCountDown
	ncountDown = TIME_MAX_LIVE - (GetTickCount() - timeStartPlay) / CLOCKS_PER_SEC;
	if (ncountDown < 0)
	{
		ncountDown = 0;
	}
	countDown = new CNumber(ncountDown,3);
	countDown->SetPosition(x + 125, y + 15);
	countDown->Update(dt);
#pragma endregion	
}

void CScoreBoard::Render()
{
	DrawBackGround();
	animation_set->at(0)->Render(x, y);
	if (countDown != NULL)
		countDown->Render();
	if (numberCoin != NULL)
		numberCoin->Render();
	if (numbertotalScore!=NULL)
		numbertotalScore->Render();
	if (energy !=NULL)
		energy->Render();
	if (pMax!=NULL)
		pMax->Render();
}

void CScoreBoard::DrawBackGround()
{
	LPDIRECT3DTEXTURE9 darken = CTextures::GetInstance()->Get(998);

	CGame::GetInstance()->Draw(x, y - 5, darken, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
}

void CScoreBoard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

