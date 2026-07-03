#include "EnemyBullet.h"
#include "DxLib.h"
#include <math.h>

void EnemyBullet::Initialize()
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    speed = 5.0f;
    isActive = false;
}

void EnemyBullet::Update()
{
    if (!isActive) return;

    x += vx;
    y += vy;

    if (x < -50 || x > 1330 || y < -50 || y > 770)
    {
        isActive = false;
    }
}

void EnemyBullet::Draw()
{
    if (!isActive) return;

    DrawCircle((int)x, (int)y, 6, GetColor(255, 80, 80), TRUE);
}

void EnemyBullet::Fire(int startX, int startY, int targetX, int targetY)
{
    if (isActive) return;

    x = (float)startX;
    y = (float)startY;

    float dx = (float)(targetX - startX);
    float dy = (float)(targetY - startY);

    float length = sqrtf(dx * dx + dy * dy);

    if (length <= 0.0f)
    {
        length = 1.0f;
    }

    vx = dx / length * speed;
    vy = dy / length * speed;

    isActive = true;
}
