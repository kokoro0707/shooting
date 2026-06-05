#include "Enemy.h"
#include "DxLib.h"

void Enemy::Initialize()
{
	speed = 3;
	Respawn();
}



void Enemy::Update()
{

	if (!isActive)
	{
		Respawn();
		return;
	}
	// 敵は下に移動
	y += speed;

	// 画面下に出たら再出現

	if (y > 760)
	{
		Respawn();
	}

}



void Enemy::Draw()
{
	if (!isActive) return;
	DrawCircle(x, y, 20, GetColor(255, 80, 80), TRUE);

}



void Enemy::Respawn()
{
	x = GetRand(1200) + 40;

	// 確認用。あとで -40 に戻してOK
	y = 100;
	isActive = true;
}


