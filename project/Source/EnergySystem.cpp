#include "EnergySystem.h"
#include "DxLib.h"

void EnergySystem::Initialize()
{
	maxEnergy = 100;
	energy = maxEnergy;
	decreaseTimer = 0;
}

void EnergySystem::Update()
{
	decreaseTimer++;

	if (decreaseTimer >= 60)
	{
		energy--;
		decreaseTimer = 0;
	}
	if (energy < 0)
	{
		energy = 0;
	}
}

void EnergySystem::Draw()
{
	DrawFormatString(20, 60, GetColor(255, 255, 255), "ENERGY;%d", energy);

	//‘Ï‹vƒQ[ƒW”wŒi
	DrawBox(20, 90, 220, 100, GetColor(80, 80, 80), TRUE);

	//‘Ï‹vƒQ[ƒW–{‘Ì
	int gugeWidth = energy * 2;
	DrawBox(20, 90, 20 + gugeWidth, 110, GetColor(0, 255, 100),TRUE);
}

void EnergySystem::Recover(int value)
{
	energy += value;

	if (energy > maxEnergy)
	{
		energy = maxEnergy;
	}
}

bool EnergySystem::UseEnergy(int value)
{
	if (energy < value)
	{
		return false;
	}
	energy -= value;
	return true;
}