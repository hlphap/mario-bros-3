#include "Text.h"

CText::CText(float x, float y, string st)
{
	this->st = st;
	SetPosition(x, y);
}

void CText::Update(DWORD dt)
{
	//in hoa
	for (int i = 0; i <= st.length(); i++) {
		if (st[i] >= 97 && st[i] <= 122)
			st[i] = st[i] - 32;
	}
	for (int i = 0; i < st.length(); i++)
	{
		if (st[i] != 32)
		{
			COneCharacter* character = new COneCharacter(st[i] - 54);
			character->SetPosition(x + 8 * i, y);
			listCharacter.push_back(character);
		}
		
	}
}

void CText::Render()
{
	for (size_t i = 0; i < listCharacter.size(); i++)
	{
		listCharacter.at(i)->Render();
	}
}

void CText::SetState(int state)
{
}

void CText::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

COneCharacter::COneCharacter(int aciiCharacter)
{
	this->aciiCharacter = aciiCharacter;
}

void COneCharacter::Update(DWORD dt)
{
}

void COneCharacter::Render()
{
	animation_set->at(aciiCharacter)->Render(x, y);
}

void COneCharacter::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
