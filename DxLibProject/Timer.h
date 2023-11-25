#pragma once
#include "DxLib.h"

class Timer {
private:
    Timer() = delete;

    static LONGLONG nowHiPerformanceCount;
    static LONGLONG beforeHiPerformanceCount;
    static float deltaTime;
    static LONGLONG hiPerformanceDeltaTime;

public:

    static void init();
    static BOOL update();
    static float getDeltaTime();
    static LONGLONG getHiPerformanceDeltaTime();

};

