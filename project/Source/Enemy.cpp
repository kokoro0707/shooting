#include "Enemy.h"
#include "DxLib.h"

void Enemy::Initialize()
{
	speed = 3;
	hp = 1;
	graphHandle = LoadGraph("data/image/redEnemy1.png");

	targetY = 120;
	moveDirection = 1;
	Respawn();
}



void Enemy::Update(int playerX,int playerY)
{

	if (!isActive)
	{
		Respawn();
		return;
	}

	//Ç‹Ç∏âÊñ è„ïîÇ‹Ç≈ç~ÇËÇƒÇ≠ÇÈ
	if (y < targetY)
	{
		y += speed;
		return;
	}

	//è„ïîÇ…Ç∆Ç«Ç‹Ç¡Çƒç∂âEà⁄ìÆ
	x += moveDirection * 2;

	if (x < 80)
	{
		x = 80;
		moveDirection = 1;
	}

	if (x > 1200)
	{
		x = 1200;
		moveDirection = -1;
	}

}



void Enemy::Draw()
{
	if (!isActive) return;
	DrawGraph(x - 16, y - 16, graphHandle, TRUE);

}



void Enemy::Respawn()
{
	x = GetRand(1200) + 40;
	y = -50;

	hp = 1;
	isActive = true;

	moveDirection = GetRand(1) == 0 ? -1 : 1;
}

void Enemy::Damage(int value)
{
	hp -= value;

	if (hp <= 0)
	{
		isActive = false;
	}
}


