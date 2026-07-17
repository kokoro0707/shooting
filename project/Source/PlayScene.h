#pragma once
#include "../Library/SceneBase.h"
#include "../Source/Player.h"
#include"../Source/Bullet.h"
#include "../Source/Enemy.h"
#include "../Source/EnergySystem.h"
#include "../Source/EnemyBullet.h"
#include "BeamEfect.h"

class PlayScene : public SceneBase
{

public:

	PlayScene();
	~PlayScene();



	void Update() override;
	void Draw() override;

private:
	void CheckCollision();



private:
	static const int ENEMY_MAX = 5;
	static const int MAX_ENEMY_BULLETS = 10;
	Player player;
	Bullet bullet;
	Enemy enemies[ENEMY_MAX];
	EnergySystem energysystem;

	int score;

private:
	void UseSpecialAttack();

	bool oldZKey;

	EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
	int enemyShotTimer;

private:
	int bulletSheetHandle;
	int playerBulletHandle;
	int enemyBulletHandle;
	 BeamEfect beamEfect;
};


