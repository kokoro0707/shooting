#pragma once
#include "../Library/SceneBase.h"
#include "../Source/Player.h"
#include"../Source/Bullet.h"
#include "../Source/Enemy.h"
#include "../Source/EnergySystem.h"

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
	Player player;
	Bullet bullet;
	Enemy enemy;
	EnergySystem energysystem;

	int score;
};


