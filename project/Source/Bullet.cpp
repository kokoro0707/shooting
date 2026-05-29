#include "Bullet.h"
#include "DxLib.h"

void Bullet::Initialize()
{
	x = 0;
	y = 0;
	speed = 0;
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

}
