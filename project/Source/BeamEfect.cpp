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

    isActive = false;
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
        DerivationGraph(1177, 20, 190, 1430, sheetHandle);

    // 透過色を元に戻す
    SetTransColor(0, 0, 0);

    x = 0;
    bottomY = 0;

    animationTimer = 0;
    currentFrame = 0;

    isActive = false;
}

void BeamEfect::Start(int playerX, int playerY)
{
    // 発動中なら再発動しない
    if (isActive)
    {
        return;
    }

    x = playerX;
    bottomY = playerY;

    animationTimer = 0;
    currentFrame = 0;

    // ここはtrue
    isActive = true;
}

void BeamEfect::Update()
{
    if (!isActive)
    {
        return;
    }

    animationTimer++;

    // 3フレームごとに次の画像へ
    if (animationTimer >= 3)
    {
        animationTimer = 0;
        currentFrame++;

        if (currentFrame >= FRAME_COUNT)
        {
            currentFrame = 0;
            isActive = false;
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
        70
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
