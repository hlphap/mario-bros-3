#include "Number.h"
#include "Utils.h"


//Number Character
CNumCharacter::CNumCharacter(int number)
{
	this->numChar = number;
}

void CNumCharacter::Render()
{
	//Tuong Ung vo numCharacter render animation
	animation_set->at(numChar+1)->Render(x, y);
}

void CNumCharacter::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	return;
}

CNumCharacter::~CNumCharacter()
{

}



//OneNumber

CNumber::CNumber(int number, int SoKiTu)
{
	this->SoKiTu = SoKiTu;
	this->number = number;
}



void CNumber::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void CNumber::Update(DWORD dt)
{
	string sNumber = (to_string)(number);
	while (SoKiTu > sNumber.length())
		sNumber = '0' + sNumber;
	for (int i = 0; i < sNumber.size(); i++)
	{
		CNumCharacter* num = new CNumCharacter(sNumber[i] - '0');
		num->SetPosition(x + 8 * i, y);
		listNumber.push_back(num);
	}
}

void CNumber::Render()
{
	for (size_t i = 0; i<listNumber.size(); i++)
	{
		listNumber.at(i)->Render();
	}
}
