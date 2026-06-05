#pragma once
class EnergySystem
{
public:
	void Initialize();
	void Update();
	void Draw();

	void Recover(int value);
	bool UseEnergy(int value);

	bool IsDead() const { return energy <= 0; }

	int GetEnergy() const { return energy; }

private:
	int energy;
	int maxEnergy;
	int decreaseTimer;
};

