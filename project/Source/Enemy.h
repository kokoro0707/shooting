#pragma once
class Enemy
{
public:
	void Initialize();
	void Update(int playerX,int playerY);
	void Draw();

	void Respawn();
	void Dectivate() { isActive = false; }

	bool IsActive() const { return isActive; }

	int GetX() const { return x; }
	int GetY() const { return y; }

public:
	void Damage(int value);

	bool IsDead() const
	{
		return hp <= 0;
	}

private:
	int x;
	int y;
	int speed;
	bool isActive;
	int hp;

	int graphHandle;

	int targetY;
	int moveDirection;

};
