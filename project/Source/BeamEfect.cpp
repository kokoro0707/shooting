#include "BeamEfect.h"
#include "DxLib.h"

BeamEfect::BeamEfect()
{
    sheetHandle = -1;

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        frameHandles[i] = -1;
    }

    x = 0;
    bottomY = 0;

    animationTimer = 0;
    currentFrame = 0;
    holdTimer = 0;

    isActive = false;
    isShrink = false;
}


BeamEfect::~BeamEfect()
{
    for (int i = 0; i < FRAME_COUNT; i++)
    {
        if (frameHandles[i] != -1)
        {
            DeleteGraph(frameHandles[i]);
        }
    }

    if (sheetHandle != -1)
    {
        DeleteGraph(sheetHandle);
    }
}

void BeamEfect::Initialize()
{
    // 青背景を透過色に設定
    SetTransColor(0, 0, 255);

    sheetHandle =
        LoadGraph("data/image/laser02blue.png");

    // 各フレームを手動で切り出す
    frameHandles[0] =
        DerivationGraph(18, 20, 156, 1430, sheetHandle);

    frameHandles[1] =
        DerivationGraph(191, 20, 199, 1430, sheetHandle);

    frameHandles[2] =
        DerivationGraph(408, 20, 173, 1430, sheetHandle);

    frameHandles[3] =
        DerivationGraph(596, 20, 178, 1430, sheetHandle);

    frameHandles[4] =
        DerivationGraph(789, 20, 177, 1430, sheetHandle);

    frameHandles[5] =
        DerivationGraph(984, 20, 178, 1430, sheetHandle);

    frameHandles[6] =
        DerivationGraph(1210, 20, 160, 1430, sheetHandle);

    // 透過色を元に戻す
    SetTransColor(0, 0, 0);

    x = 0;
    bottomY = 0;

    animationTimer = 0;
    currentFrame = 0;
    holdTimer = 0;

    isActive = false;
}

void BeamEfect::Start(int playerX, int playerY)
{
    if (isActive)
    {
        return;
    }

    x = playerX;
    bottomY = playerY - 25;

    animationTimer = 0;
    currentFrame = 0;
    holdTimer = 0;
    isShrink = false;

    isActive = true;
}



void BeamEfect::Update()
{
    if (!isActive)
    {
        return;
    }

    animationTimer++;

    // 4フレームごとに切り替え
    if (animationTimer < 4)
    {
        return;
    }

    animationTimer = 0;

    // 太くなる途中
    if (!isShrink)
    {
        currentFrame++;

        if (currentFrame >= FRAME_COUNT - 1)
        {
            currentFrame = FRAME_COUNT - 1;

            holdTimer++;

            // 最大状態を30フレーム維持
            if (holdTimer >= 18)
            {
                isShrink = true;
            }
        }
    }
    // 細くなる途中
    else
    {
        currentFrame--;

        if (currentFrame <= 0)
        {
            currentFrame = 0;

            isActive = false;
            isShrink = false;
            holdTimer = 0;
        }
    }
}



void BeamEfect::Draw()
{
    if (!isActive)
    {
        return;
    }

    if (frameHandles[currentFrame] == -1)
    {
        return;
    }

    const int beamWidths[FRAME_COUNT] =
    {
        4,
        8,
        14,
        22,
        34,
        54,
        70,
        
    };

    const int beamWidth =
        beamWidths[currentFrame];

    DrawExtendGraph(
        x - beamWidth / 2,
        0,
        x + beamWidth / 2,
        bottomY,
        frameHandles[currentFrame],
        TRUE
    );
}
int BeamEfect::GetX() const
{
    return x;
}

int BeamEfect::GetY() const
{
    return 0;
}

int BeamEfect::GetBottomY() const
{
    return bottomY;
}

int BeamEfect::GetWidth() const
{
    const int beamWidths[FRAME_COUNT] =
    {
        4,
        8,
        14,
        22,
        34,
        54,
        70
    };

    if (currentFrame < 0 ||
        currentFrame >= FRAME_COUNT)
    {
        return 0;
    }

    return beamWidths[currentFrame];
}
