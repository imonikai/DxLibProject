#include "FpsControll.h"

int FpsControll::FPS; //設定したいfps
float FpsControll::fps;
int FpsControll::measureStartTime;
int FpsControll::frameCount;
int FpsControll::calcFpsInterval; //fpsを計算するフレーム間隔

void FpsControll::init()
{
    FPS = 60;
    measureStartTime = 0;
    frameCount = 0;
    calcFpsInterval = 60;
}

BOOL FpsControll::update()
{
    if (frameCount == 0)
    {
        measureStartTime = GetNowCount();
    }

    if (frameCount == calcFpsInterval)
    {
        int t = GetNowCount();
        fps = 1000.0f / ((t - measureStartTime) / (float)calcFpsInterval );
        frameCount = 0;
        measureStartTime = t;
    }

    frameCount++;

    return TRUE;
}

BOOL FpsControll::wait()
{
    int tookTime = GetNowCount() - measureStartTime;
    int wait = frameCount * 1000 / FPS - tookTime;
    if (wait > 0)
    {
        WaitTimer(wait);
    }

    return TRUE;
}

float FpsControll::getFps()
{
    return fps;
}
