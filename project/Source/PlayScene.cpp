#include "PlayScene.h"

#include "DxLib.h"
#include "../Library/SceneManager.h"


PlayScene::PlayScene()
{
    // 各オブジェクトの初期化
    player.Initialize();
    bulletSheetHandle = LoadGraph("data/image/stg07101.png");
    playerBulletHandle = DerivationGraph(352, 46, 40, 52, bulletSheetHandle);
    enemyBulletHandle = DerivationGraph(112, 46, 40, 52, bulletSheetHandle);
    bullet.Initialize(playerBulletHandle);
    enemy.Initialize();
    energysystem.Initialize();

    // 敵弾をすべて初期化
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        enemyBullets[i].Initialize(enemyBulletHandle);
    }

    score = 0;

    enemyShotTimer = 0;

    specialEffectTimer = 0;
    oldZKey = false;
}


PlayScene::~PlayScene()
{
}


void PlayScene::Update()
{
    // プレイヤー更新
    player.Update(bullet);

    // プレイヤー弾更新
    bullet.Update();

    // 敵更新
    enemy.Update(
        player.GetX(),
        player.GetY()
    );

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
        if (enemy.IsActive())
        {
            // 使用されていない敵弾を探す
            for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
            {
                if (!enemyBullets[i].IsActive())
                {
                    enemyBullets[i].Fire(
                        enemy.GetX(),
                        enemy.GetY(),
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

    // 大技エフェクトの時間を減らす
    if (specialEffectTimer > 0)
    {
        specialEffectTimer--;
    }

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
    enemy.Draw();

    // 敵弾をすべて表示
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        enemyBullets[i].Draw();
    }

    // 大技エフェクト
    if (specialEffectTimer > 0)
    {
        // プレイヤーから画面上部へレーザーを表示
        DrawBox(
            player.GetX() - 25,
            0,
            player.GetX() + 25,
            player.GetY(),
            GetColor(0, 220, 255),
            TRUE
        );

        // 外側の白い光
        DrawBox(
            player.GetX() - 10,
            0,
            player.GetX() + 10,
            player.GetY(),
            GetColor(255, 255, 255),
            TRUE
        );
    }

    // 操作説明
    DrawString(20,660,"Move : WASD / Arrow", GetColor(255, 255, 255));

    DrawString( 20,680,"Shot : SPACE",GetColor(255, 255, 255));

    DrawString(20,700, "Special Attack : Z", GetColor(255, 255, 255));
}


void PlayScene::CheckCollision()
{
    //========================================
    // プレイヤー弾と敵の当たり判定
    //========================================

    if (enemy.IsActive() && bullet.IsActive())
    {
        int dx = enemy.GetX() - bullet.GetX();
        int dy = enemy.GetY() - bullet.GetY();

        int distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < 25 * 25)
        {
            // プレイヤー弾を消す
            bullet.Deactivate();

            // 敵に1ダメージ
            enemy.Damage(1);
        }

        // 敵を倒した場合
        if (enemy.IsDead())
        {
            score += 100;

            // 敵撃破で耐久値を5回復
            energysystem.Recover(5);

            // 敵を再出現させる
            enemy.Respawn();
        }
    }


    //========================================
    // 敵弾とプレイヤーの当たり判定
    //========================================

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!enemyBullets[i].IsActive())
        {
            continue;
        }

        int dx =
            player.GetX() -
            enemyBullets[i].GetX();

        int dy =
            player.GetY() -
            enemyBullets[i].GetY();

        int distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < 25 * 25)
        {
            // 敵弾を消す
            enemyBullets[i].Deactivate();

            // 耐久値を10減らす
            energysystem.Damage(10);
        }
    }


    //========================================
    // 敵本体とプレイヤーの当たり判定
    //========================================

    if (enemy.IsActive())
    {
        int dx = player.GetX() - enemy.GetX();
        int dy = player.GetY() - enemy.GetY();

        int distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < 35 * 35)
        {
            // 接触した敵を再出現させる
            enemy.Respawn();

            // プレイヤーの耐久値を20減らす
            energysystem.Damage(20);
        }
    }
}


void PlayScene::UseSpecialAttack()
{
    bool currentZKey =
        CheckHitKey(KEY_INPUT_Z) != 0;

    // Zキーを押した瞬間だけ処理する
    if (currentZKey && !oldZKey)
    {
        // 耐久値を20消費できる場合
        if (energysystem.UseEnergy(20))
        {
            specialEffectTimer = 15;

            // 敵を倒す
            if (enemy.IsActive())
            {
                enemy.Damage(999);

                score += 300;

                enemy.Respawn();
            }

            // 画面上の敵弾をすべて消す
            for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
            {
                enemyBullets[i].Deactivate();
            }
        }
    }

    oldZKey = currentZKey;
}
