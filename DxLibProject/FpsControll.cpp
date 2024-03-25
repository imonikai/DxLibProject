#include "FpsControll.h"

void FpsControll::init(int fps)
{
    setFps(fps);
    measureStartTime = 0;
    frameCount = 0;
}

void FpsControll::setFps(int fps)
{
    FPS = fps;
    calcFpsInterval = fps;
}

BOOL FpsControll::update()
{
    wait();

    if (frameCount == 0)
    {
        measureStartTime = GetNowCount();
    }

    if (frameCount == calcFpsInterval)
    {
        int t = GetNowCount();
        fps = 1000.0f / ((t - measureStartTime) / (float)calcFpsInterval);
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

LONGLONG FpsControll::getFrameCount()
{
    return frameCount;
}
