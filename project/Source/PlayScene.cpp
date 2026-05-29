
#include "PlayScene.h"
#include "DxLib.h"

PlayScene::PlayScene()
{

	playerX = 640;

	playerY = 600;

	playerSpeed = 6;



	bulletX = 0;

	bulletY = 0;

	bulletActive = false;



	enemyX = 640;

	enemyY = 100;

	enemyActive = true;



	score = 0;

	timer = 0;

}



PlayScene::~PlayScene()
{

}



void PlayScene::Update()
{

	timer++;



	// ŽžŠÔŒo‰ß‚ÅŽã‘Ì‰»

	if (timer % 600 == 0 && playerSpeed > 2)
	{

		playerSpeed--;

	}



	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{

		playerX -= playerSpeed;

	}

	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{

		playerX += playerSpeed;

	}

	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{

		playerY -= playerSpeed;

	}

	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{

		playerY += playerSpeed;

	}



	if (playerX < 20) playerX = 20;

	if (playerX > 1260) playerX = 1260;

	if (playerY < 20) playerY = 20;

	if (playerY > 700) playerY = 700;



	// ’e”­ŽË

	if (CheckHitKey(KEY_INPUT_SPACE) && bulletActive == false)
	{

		bulletX = playerX;

		bulletY = playerY;

		bulletActive = true;

	}



	// ’eˆÚ“®

	if (bulletActive)
	{

		bulletY -= 12;

		if (bulletY < 0)
		{

			bulletActive = false;

		}

	}



	// “G‚Æ’e‚Ì“–‚½‚è”»’è
	if (enemyActive && bulletActive)
	{

		if (abs(enemyX - bulletX) < 25 && abs(enemyY - bulletY) < 25)
		{

			enemyActive = false;

			bulletActive = false;

			score += 100;

		}

	}



	// “G‚ª‚¢‚È‚¯‚ê‚Î•œŠˆ

	if (enemyActive == false)
	{

		enemyX = GetRand(1200) + 40;

		enemyY = GetRand(200) + 40;

		enemyActive = true;

	}



	if (CheckHitKey(KEY_INPUT_T))
	{

		SceneManager::ChangeScene("TITLE");

	}

}



void PlayScene::Draw()
{

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawFormatString(0, 30, GetColor(255, 255, 255), "SCORE : %d", score);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "SPEED : %d", playerSpeed);



	// Ž©‹@
	DrawBox(playerX - 15, playerY - 15, playerX + 15, playerY + 15, GetColor(0, 200, 255), TRUE);

	// ’e
	if (bulletActive)
	{

		DrawCircle(bulletX, bulletY, 6, GetColor(255, 255, 0), TRUE);
	}



	// “G
	if (enemyActive)
	{
		DrawCircle(enemyX, enemyY, 20, GetColor(255, 80, 80), TRUE);

	}

	DrawString(100, 400, "Push [T] Key To Title", GetColor(255, 255, 255));

}


