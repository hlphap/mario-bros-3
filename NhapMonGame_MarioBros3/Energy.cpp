#include "Energy.h"

void C1Energy::Update(DWORD dt)
{

}

void C1Energy::Render()
{
	animation_set->at(37)->Render(x, y);
}

void C1Energy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

CEnergy::CEnergy(int numEnergy)
{
	this->numEnergy = numEnergy;
}

void CEnergy::Update(DWORD dt)
{
	for (size_t i = 0; i < numEnergy; i++)
	{
		C1Energy* energy = new C1Energy();
		energy->SetPosition(x + 8 * i, y);
		listEnergy.push_back(energy);
	}
}

void CEnergy::Render()
{
	for (size_t i = 0; i < listEnergy.size(); i++)
	{
		listEnergy.at(i)->Render();
	}
}

void CEnergy::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
