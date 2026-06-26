#include "Player.h"
#include "Bullet.h"
#include "DxLib.h"
#include "Screen.h"

void Player::Initialize()
{

	x = 640;
	y = 600;
	speed = 6;

	graphHandle = LoadGraph("data/image/player2.png");
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
	if (x < 15)x = 15;
	if (x > 1280-15)x = 1280-15;

	if (y < 15)x = 15;
	if (y > 720-15)x = 720-15;
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
	DrawGraph(x - 16, y - 16, graphHandle, TRUE);
 }