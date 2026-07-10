#include "EnemyBullet.h"
#include "DxLib.h"
#include <cmath>

void EnemyBullet::Initialize(int handle)
{
    x = 0.0f;
    y = 0.0f;

    velocityX = 0.0f;
    velocityY = 0.0f;

    speed = 5.0f;
    isActive = false;

    graphHandle = handle;
}

void EnemyBullet::Update()
{
    if (!isActive)
    {
        return;
    }

    x += velocityX;
    y += velocityY;

    if (x < -50.0f ||
        x > 1330.0f ||
        y < -50.0f ||
        y > 770.0f)
    {
        isActive = false;
    }
}

void EnemyBullet::Draw()
{
    if (!isActive)
    {
        return;
    }

    DrawRotaGraph(
        static_cast<int>(x),
        static_cast<int>(y),
        0.35,
        0.0,
        graphHandle,
        TRUE
    );
}

void EnemyBullet::Fire(
    int startX,
    int startY,
    int targetX,
    int targetY)
{
    if (isActive)
    {
        return;
    }

    x = static_cast<float>(startX);
    y = static_cast<float>(startY);

    const float dx =
        static_cast<float>(targetX - startX);

    const float dy =
        static_cast<float>(targetY - startY);

    float length = std::sqrt(
        dx * dx + dy * dy
    );

    if (length <= 0.0f)
    {
        length = 1.0f;
    }

    velocityX = dx / length * speed;
    velocityY = dy / length * speed;

    isActive = true;
}
