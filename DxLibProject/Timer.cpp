#include "Timer.h"

LONGLONG Timer::nowTime;
LONGLONG Timer::beforeFrameHiPerformanceCount;
float Timer::deltaTime;
LONGLONG Timer::fpsCheckTime;
int Timer::fps;
int Timer::fpsCounter;

void Timer::init() {
    nowTime = GetNowHiPerformanceCount();
    beforeFrameHiPerformanceCount = nowTime;
    deltaTime = 0.0f;
    fpsCheckTime = nowTime;
    fps = 0;
    fpsCounter = 0;
}

BOOL Timer::update() {
    LONGLONG tmpNowTime = nowTime;
    nowTime = GetNowHiPerformanceCount();

    deltaTime = ( nowTime - beforeFrameHiPerformanceCount ) / 1000000.0f;

    beforeFrameHiPerformanceCount = tmpNowTime;

    fpsCounter++;
    if (nowTime - fpsCheckTime >= 1000000)
    {
        fps = fpsCounter;
        fpsCounter = 0;
        fpsCheckTime = nowTime;
    }


    return TRUE;
}

float Timer::getDeltaTime() {
    return deltaTime;
}

void Timer::drawFps(int x, int y) {
    DrawFormatString(x, y, GetColor(255, 255, 255), _T("%d"), fps);
}

void Timer::drawFps(int x, int y, int fontHandle) {
    DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), fontHandle, _T("FPS: %d"), fps);
}
