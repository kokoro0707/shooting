#pragma once
class Bullet;

class Player
{
public:
	void Initialize();
	void Update(Bullet& bullet);
	void Draw();

	int GetX() const { return x; }
	int GetY() const { return y; }

private:
	void Move();
	void Shoot(Bullet& bullet);

private:
	int x;
	int y;
	int speed;

	int graphHandle;
};
