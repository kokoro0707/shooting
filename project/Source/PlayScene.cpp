#include "PlayScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"

PlayScene::PlayScene()
{
	player.Initialize();
	bullet.Initialize();
	enemy.Initialize();
	energysystem.Initialize();

	score = 0;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	player.Update(bullet);
	bullet.Update();
	enemy.Update();
	energysystem.Update();

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
}