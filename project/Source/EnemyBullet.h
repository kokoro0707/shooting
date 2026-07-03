#pragma once
class EnemyBullet
{
public:
	void Initialize();
	void Update();
	void Draw();

	void Fire(int startX, int startY, int targetX, int targetY);
	bool IsActive()const { return isActive; }
	void Deactivate() { isActive = false; }

	int GetX() const { return x; }
	int GetY() const { return y; }

private:
	float x;
	float y;
	float vx;
	float vy;
	float speed;

	bool isActive;

};

