#include "Bullet.h"
#include "DxLib.h"

void Bullet::Initialize(int handle)
{
    x = 0.0f;
    y = 0.0f;

    speed = 12.0f;
    isActive = false;

    graphHandle = handle;
}

void Bullet::Update()
{
    if (!isActive)
    {
        return;
    }

    y -= speed;

    if (y < -30.0f)
    {
        isActive = false;
    }
}

void Bullet::Draw()
{
    if (!isActive)
    {
        return;
    }

    // Œ³‰æ‘œ‚ª‘å‚«‚¢‚½‚ßk¬•\Ž¦
    DrawRotaGraph(
        static_cast<int>(x),
        static_cast<int>(y),
        0.35,
        0.0,
        graphHandle,
        TRUE
    );
}

void Bullet::Fire(int startX, int startY)
{
    if (isActive)
    {
        return;
    }

    x = static_cast<float>(startX);
    y = static_cast<float>(startY - 25);

    isActive = true;
}
