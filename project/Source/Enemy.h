#pragma once
class Enemy
{
public:
	void Initialize();
	void Update();
	void Draw();

	void Respawn();
	void Dectivate() { isActive = false; }

	bool IsActive() const { return isActive; }

	int GetX() const { return x; }
	int GetY() const { return y; }

private:
	int x;
	int y;
	int speed;
	bool isActive;
};

