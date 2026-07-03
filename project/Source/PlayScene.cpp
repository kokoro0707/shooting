#include "PlayScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "EnergySystem.h"

PlayScene::PlayScene()
{
	player.Initialize();
	bullet.Initialize();
	enemy.Initialize();
	energysystem.Initialize();

	score = 0;
	specialEfectTimer = 0;
	oldZKey = false;
	enemyBullet.Initialize();
	enemyShotTimer = 0;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	player.Update(bullet);
	bullet.Update();
	enemy.Update(player.GetX(),player.GetY());
	energysystem.Update();
	enemyBullet.Update();

	if (enemyShotTimer = 90)
	{
		if (enemy.IsActive())
		{
			enemyBullet.Fire(enemy.GetX(), enemy.GetY(), player.GetX(), player.GetY());
		}
		enemyShotTimer = 0;
	}

	UseSpecialAttack();
	if (specialEfectTimer > 0)
	{
		specialEfectTimer--;
	}
	CheckCollision();

	if (energysystem.IsDead())
	{
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_T))
	{
		SceneManager::ChangeScene("TITLE");
	}
}
void PlayScene::CheckCollision()
{
	if (!enemy.IsActive())return;
	if (!bullet.IsActive())return;

	int dx = enemy.GetX() - bullet.GetX();
	int dy = enemy.GetY() - bullet.GetY();

	int distance = dx * dx + dy * dy;

	if (distance < 25 * 25)
	{
		bullet.Deactivate();

		enemy.Damage(1);
	}

	if (enemy.IsDead())
	{
		score += 100;
		energysystem.Recover(5);

		enemy.Respawn();
	}

	if (enemyBullet.IsActive())
	{
		int dx = player.GetX() - enemyBullet.GetX();
		int dy = player.GetY() - enemyBullet.GetY();

		if (dx * dx + dy * dy < 25 * 25)
		{
			enemyBullet.Deactivate();
			energysystem.Damage(10);
		}
	}
}
void PlayScene::UseSpecialAttack()
{
	bool nowZKey = CheckHitKey(KEY_INPUT_Z);
	if (nowZKey && !oldZKey)
	{
		if (enemy.IsActive())
		{
			if (energysystem.UseEnergy(20))
			{
				enemy.Damage(20);

				score += 300;

				specialEfectTimer = 10;
			}
		}
	}
	oldZKey = nowZKey;
}

void PlayScene::Draw()
{
	DrawString(20, 20, "PLAY SCENE", GetColor(255, 255, 255));
	DrawFormatString(20, 40, GetColor(255, 255, 255), "SCORE: %d", score);

	energysystem.Draw();

	player.Draw();
	bullet.Draw();
	enemy.Draw();

	DrawString(20, 680, "Move : WASD / Arrow", GetColor(255, 255, 255));
	DrawString(20, 700, "Shot : SPASE", GetColor(255, 255, 255));
	if (specialEfectTimer > 0)
	{
		DrawBox(0, 0, 1280, 720, GetColor(0, 180, 255),FALSE);

		DrawLine(player.GetX(), player.GetY(), enemy.GetX(), enemy.GetY(), GetColor(0, 255, 255));
	}
	enemyBullet.Draw();
}