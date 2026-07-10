#pragma once

class EnemyBullet
{
public:
    void Initialize(int handle);
    void Update();
    void Draw();

    void Fire(
        int startX,
        int startY,
        int targetX,
        int targetY
    );

    bool IsActive() const
    {
        return isActive;
    }

    void Deactivate()
    {
        isActive = false;
    }

    int GetX() const
    {
        return static_cast<int>(x);
    }

    int GetY() const
    {
        return static_cast<int>(y);
    }

private:
    float x;
    float y;

    float velocityX;
    float velocityY;

    float speed;
    bool isActive;

    int graphHandle;
};
