#pragma once

class BeamEfect
{
public:
    BeamEfect();
    ~BeamEfect();

    // ‰æ‘œ“Ç‚İ‚İ
    void Initialize();

    // •KE‹Z‚ğ”­“®
    void Start(int playerX, int playerY);

    void Update();
    void Draw();
    int GetX()const;
    int GetY()const;
    int GetBottomY()const;
    int GetWidth()const;

    bool IsActive() const
    {
        return isActive;
    }

private:
    static const int FRAME_COUNT = 7;

    int sheetHandle;
    int frameHandles[FRAME_COUNT];

    int x;
    int bottomY;

    int animationTimer;
    int currentFrame;

    int holdTimer;

    bool isActive;
    bool isShrink;
};
