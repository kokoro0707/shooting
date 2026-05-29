#include "Player.h"
#include "Bullet.h"
#include "DxLib.h"

void Player::Initialize()
{
	x = 640;
	y = 600;
	speed = 6;
}

void Player::Update(Bullet& bullet)
{
	Move();
	Shoot(bullet);
}
void Player::Move()
{
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT))
	{
		x -= speed;
	}
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT))
	{
		x += speed;
	}
	if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
	{
		y -= speed;
	}
	if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN))
	{
		y += speed;
	}
	if (x < 20)x = 20;
	if (x < 1260)x = 1260;
	if (x < 20)x = 20;
	if (x < 700)x = 700;
}

void Player::Shoot(Bullet& bullet)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		bullet.Fire(x, y);
	}
}
void Player::Draw()
{
	DrawBox(x - 15, y - 15, x + 15, y + 15, GetColor(0, 200, 255), TRUE);
 }