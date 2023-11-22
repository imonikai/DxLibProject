#include "Timer.h"

LONGLONG Timer::nowHiPerformanceCount;
LONGLONG Timer::beforeFrameHiPerformanceCount;
float Timer::deltaTime;
LONGLONG Timer::hiPerformanceDeltaTime;
LONGLONG Timer::fpsCheckTime;
int Timer::fps;
int Timer::fpsCounter;

void Timer::init() {
    nowHiPerformanceCount = GetNowHiPerformanceCount();
    beforeFrameHiPerformanceCount = nowHiPerformanceCount;
    deltaTime = 0;
    hiPerformanceDeltaTime = 0;
    fpsCheckTime = nowHiPerformanceCount;
    fps = 0;
    fpsCounter = 0;
}

BOOL Timer::update() {
    beforeFrameHiPerformanceCount = nowHiPerformanceCount;
    nowHiPerformanceCount = GetNowHiPerformanceCount();

    hiPerformanceDeltaTime = (nowHiPerformanceCount - beforeFrameHiPerformanceCount);
    deltaTime = ( nowHiPerformanceCount - beforeFrameHiPerformanceCount ) / 1000000.0f;

    fpsCounter++;
    if (nowHiPerformanceCount - fpsCheckTime >= 1000000)
    {
        fps = fpsCounter;
        fpsCounter = 0;
        fpsCheckTime = nowHiPerformanceCount;
    }

    return TRUE;
}

float Timer::getDeltaTime() {
    return deltaTime;
}

LONGLONG Timer::getHiPerformanceDeltaTime() {
    return hiPerformanceDeltaTime;
}

void Timer::drawFps(int x, int y) {
    DrawFormatString(x, y, GetColor(255, 255, 255), _T("%d"), fps);
}

void Timer::drawFps(int x, int y, int fontHandle) {
    DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), fontHandle, _T("FPS: %d"), fps);
}
