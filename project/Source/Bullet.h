#pragma once
class Bullet
{
public:
	void Initialize(int handle);
	void Update();
	void Draw();

	void Fire(int startX, int startY);

	bool IsActive() const { return isActive; }
	void Deactivate() { isActive = false; }

	int GetX() const { return x; }
	int GetY() const { return y; }

private:
	int x;
	int y;
	int speed;
	int isActive;
	int graphHandle;
};

