#include "PlayScene.h"

#include "DxLib.h"
#include "../Library/SceneManager.h"

PlayScene::PlayScene()
{
    player.Initialize();

    bulletSheetHandle =
        LoadGraph("data/image/stg07101.png");

    playerBulletHandle =
        DerivationGraph(
            352,
            46,
            40,
            52,
            bulletSheetHandle
        );

    enemyBulletHandle =
        DerivationGraph(
            112,
            46,
            40,
            52,
            bulletSheetHandle
        );

    bullet.Initialize(playerBulletHandle);
    for (int i = 0;i < ENEMY_MAX;i++)
    {
        enemies[i].Initialize();
    }
    energysystem.Initialize();

    // ビームを初期化
    beamEfect.Initialize();

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        enemyBullets[i].Initialize(enemyBulletHandle);
    }

    score = 0;
    enemyShotTimer = 0;
    oldZKey = false;
}


PlayScene::~PlayScene()
{
    if (playerBulletHandle != -1)
    {
        DeleteGraph(playerBulletHandle);
        playerBulletHandle = -1;
    }

    if (enemyBulletHandle != -1)
    {
        DeleteGraph(enemyBulletHandle);
        enemyBulletHandle = -1;
    }

    if (bulletSheetHandle != -1)
    {
        DeleteGraph(bulletSheetHandle);
        bulletSheetHandle = -1;
    }
}




void PlayScene::Update()
{
    // プレイヤー更新
    player.Update(bullet);

    // プレイヤー弾更新
    bullet.Update();

    // 敵更新
    for (int i = 0;i < ENEMY_MAX;i++)
    {
        enemies[i].Update(
            player.GetX(),
            player.GetY()
        );
    }

    // 耐久値更新
    energysystem.Update();

    // 敵弾をすべて更新
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        enemyBullets[i].Update();
    }

    // 敵の射撃タイマー
    enemyShotTimer++;

    // 90フレームごとに射撃
    if (enemyShotTimer >= 90)
    {
        for (int e = 0; e < ENEMY_MAX; e++)
        {
            if (!enemies[e].IsActive())
                continue;

            for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
            {
                if (!enemyBullets[i].IsActive())
                {
                    enemyBullets[i].Fire(
                        enemies[e].GetX(),
                        enemies[e].GetY(),
                        player.GetX(),
                        player.GetY()
                    );
                    break;
                }
            }
        }


        enemyShotTimer = 0;
    }

    // 大技処理
    UseSpecialAttack();

    beamEfect.Update();
    // 各種当たり判定
    CheckCollision();

    // 耐久値が0ならタイトルへ戻る
    if (energysystem.IsDead())
    {
        SceneManager::ChangeScene("TITLE");
    }

    // Tキーでタイトルへ戻る
    if (CheckHitKey(KEY_INPUT_T))
    {
        SceneManager::ChangeScene("TITLE");
    }
}


void PlayScene::Draw()
{
    // UI表示
    DrawString(
        20,
        20,
        "PLAY SCENE",
        GetColor(255, 255, 255)
    );

    DrawFormatString(
        20,
        40,
        GetColor(255, 255, 255),
        "SCORE : %d",
        score
    );

    // 耐久ゲージ表示
    energysystem.Draw();

    // プレイヤー表示
    player.Draw();

    // プレイヤー弾表示
    bullet.Draw();

    // 敵表示
    for (int i = 0;i < ENEMY_MAX;i++)
    {
        enemies[i].Draw();
    }

    // 敵弾をすべて表示
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        enemyBullets[i].Draw();
    }

    // 大技エフェクト
    beamEfect.Draw();

    // 操作説明
    DrawString(20,660,"Move : WASD / Arrow", GetColor(255, 255, 255));

    DrawString( 20,680,"Shot : SPACE",GetColor(255, 255, 255));

    DrawString(20,700, "Special Attack : Z", GetColor(255, 255, 255));
}


void PlayScene::CheckCollision()
{
    //========================================
    // ビームと敵
    //========================================
    if (beamEfect.IsActive())
    {
        const int beamX = beamEfect.GetX();
        const int beamHalfWidth = beamEfect.GetWidth() / 2;

        const int beamLeft = beamX - beamHalfWidth;
        const int beamRight = beamX + beamHalfWidth;
        const int beamTop = 0;
        const int beamBottom = beamEfect.GetBottomY();

        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (!enemies[i].IsActive())
            {
                continue;
            }

            const int enemyHalfWidth = 20;
            const int enemyHalfHeight = 20;

            const int enemyLeft = enemies[i].GetX() - enemyHalfWidth;
            const int enemyRight = enemies[i].GetX() + enemyHalfWidth;
            const int enemyTop = enemies[i].GetY() - enemyHalfHeight;
            const int enemyBottom = enemies[i].GetY() + enemyHalfHeight;

            const bool hitX =
                beamLeft <= enemyRight &&
                beamRight >= enemyLeft;

            const bool hitY =
                beamTop <= enemyBottom &&
                beamBottom >= enemyTop;

            if (hitX && hitY)
            {
                enemies[i].Damage(999);

                score += 300;
                energysystem.Recover(5);

                enemies[i].Respawn();
            }
        }
    }

    //========================================
    // プレイヤー弾と敵
    //========================================
    if (bullet.IsActive())
    {
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (!enemies[i].IsActive())
            {
                continue;
            }

            const int dx =
                enemies[i].GetX() - bullet.GetX();

            const int dy =
                enemies[i].GetY() - bullet.GetY();

            const int distanceSquared =
                dx * dx + dy * dy;

            if (distanceSquared < 25 * 25)
            {
                bullet.Deactivate();

                enemies[i].Damage(1);

                if (enemies[i].IsDead())
                {
                    score += 100;

                    energysystem.Recover(5);

                    enemies[i].Respawn();
                }

                break;
            }
        }
    }

    //========================================
    // 敵弾とプレイヤー
    //========================================
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!enemyBullets[i].IsActive())
        {
            continue;
        }

        const int dx =
            player.GetX() - enemyBullets[i].GetX();

        const int dy =
            player.GetY() - enemyBullets[i].GetY();

        const int distanceSquared =
            dx * dx + dy * dy;

        if (distanceSquared < 25 * 25)
        {
            enemyBullets[i].Deactivate();

            energysystem.Damage(10);
        }
    }

    //========================================
    // 敵本体とプレイヤー
    //========================================
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        if (!enemies[i].IsActive())
        {
            continue;
        }

        const int dx =
            player.GetX() - enemies[i].GetX();

        const int dy =
            player.GetY() - enemies[i].GetY();

        const int distanceSquared =
            dx * dx + dy * dy;

        if (distanceSquared < 35 * 35)
        {
            enemies[i].Respawn();

            energysystem.Damage(20);
        }
    }
}



void PlayScene::UseSpecialAttack()
{
    const bool currentZKey =
        CheckHitKey(KEY_INPUT_Z) != 0;

    if (currentZKey && !oldZKey)
    {
        if (!beamEfect.IsActive())
        {
            if (energysystem.UseEnergy(20))
            {
                beamEfect.Start(
                    player.GetX(),
                    player.GetY()
                );

                // 敵弾をすべて消す
                for (int i = 0;
                    i < MAX_ENEMY_BULLETS;
                    i++)
                {
                    enemyBullets[i].Deactivate();
                }
            }
        }
    }

    oldZKey = currentZKey;
}
