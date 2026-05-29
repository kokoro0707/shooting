#pragma once
#include "../Library/SceneBase.h"

class PlayScene : public SceneBase
{

public:

	PlayScene();
	~PlayScene();



	void Update() override;
	void Draw() override;



private:

	int playerX;
	int playerY;
	int playerSpeed;

	int bulletX;
	int bulletY;
	bool bulletActive;

	int enemyX;
	int enemyY;
	bool enemyActive;

	int score;
	int timer;
	int durability;

};


