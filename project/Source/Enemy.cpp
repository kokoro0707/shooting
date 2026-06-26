#include "Enemy.h"
#include "DxLib.h"

void Enemy::Initialize()
{
	speed = 3;
	hp = 1;
	graphHandle = LoadGraph("data/image/redEnemy1.png");
	Respawn();
}



void Enemy::Update()
{

	if (!isActive)
	{
		Respawn();
		return;
	}
	// “G‚Í‰º‚ÉˆÚ“®
	y += speed;

	// ‰æ–Ê‰º‚Éo‚½‚çÄoŒ»

	if (y > 760)
	{
		Respawn();
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

	hp = -1;
	isActive = true;
}

void Enemy::Damage(int value)
{
	hp -= value;

	if (hp <= 0)
	{
		isActive = false;
	}
}


