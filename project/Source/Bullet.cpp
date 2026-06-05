#include "Bullet.h"
#include "DxLib.h"

void Bullet::Initialize()
{
	x = 0;
	y = 0;
	speed = 12;
	isActive = false;
}

void Bullet::Update()
{
	if (!isActive)return;
	y -= speed;

	if (y < 0)
	{
		isActive = false;
	}
}
void Bullet::Fire(int startX, int startY)
{
	if (isActive) return;

	x = startX;
	y = startY-20;
	isActive = true;
}
void Bullet::Draw()
{
	if (!isActive)return;

	DrawCircle(x, y, 6, GetColor(255, 255, 0), TRUE);
}

