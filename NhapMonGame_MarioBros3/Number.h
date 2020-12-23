#pragma once
#include "HUD.h"
#include "Camera.h"
class CNumCharacter:public CHUD
{
public:
	int numChar;
public:
	CNumCharacter(int number);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	~CNumCharacter();
};


class CNumber: public CGameObject
{
public:
	int number;
	int SoKiTu;
	vector<CNumCharacter*> listNumber;
public:
	CNumber(int number, int SoKiTu); // Khoi tao numChar detect thanh listNumber (0,1,2,3,4)
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt);
	void Render();
};
