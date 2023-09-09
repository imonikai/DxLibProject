#include "Timer.h"

LONGLONG Timer::nowTime;
LONGLONG Timer::beforeFrameHiPerformanceCount;
float Timer::deltaTime;
LONGLONG Timer::fpsCheckTime;
int Timer::fps;
int Timer::fpsCounter;

void Timer::init()
{
    nowTime = GetNowHiPerformanceCount();
    beforeFrameHiPerformanceCount = nowTime;
    deltaTime = 0.0f;
    fpsCheckTime = nowTime;
    fps = 0;
    fpsCounter = 0;
}

BOOL Timer::update()
{
    LONGLONG tmpNowTime = nowTime;
    nowTime = GetNowHiPerformanceCount();

    deltaTime = ( nowTime - beforeFrameHiPerformanceCount ) / 1000000.0f;

    beforeFrameHiPerformanceCount = tmpNowTime;

    fpsCounter++;
    if (nowTime - fpsCheckTime > 1000000)
    {
        fps = fpsCounter;
        fpsCounter = 0;
        fpsCheckTime = nowTime;
    }


    return TRUE;
}

float Timer::getDeltaTime()
{
    return deltaTime;
}

void Timer::drawFps(const int x, const int y)
{
    DrawFormatString(x, y, GetColor(255, 255, 255), _T("FPS: %d"), fps);
}