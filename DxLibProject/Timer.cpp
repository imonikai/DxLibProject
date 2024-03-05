#include "Timer.h"

void Timer::init() {
    nowHiPerformanceCount = GetNowHiPerformanceCount();
    beforeHiPerformanceCount = nowHiPerformanceCount;
    deltaTime = 0;
    hiPerformanceDeltaTime = 0;
}

BOOL Timer::update() {
    beforeHiPerformanceCount = nowHiPerformanceCount;
    nowHiPerformanceCount = GetNowHiPerformanceCount();

    hiPerformanceDeltaTime = (nowHiPerformanceCount - beforeHiPerformanceCount);
    deltaTime = ( nowHiPerformanceCount - beforeHiPerformanceCount ) / 1000000.0f;

    return TRUE;
}

float Timer::getDeltaTime() {
    return deltaTime;
}

LONGLONG Timer::getHiPerformanceDeltaTime() {
    return hiPerformanceDeltaTime;
}
