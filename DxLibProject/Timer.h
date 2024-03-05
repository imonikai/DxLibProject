#pragma once
#include "DxLib.h"

class Timer {
private:
    Timer() = delete;

    static inline LONGLONG nowHiPerformanceCount;
    static inline LONGLONG beforeHiPerformanceCount;
    static inline float deltaTime;
    static inline LONGLONG hiPerformanceDeltaTime;

public:

    static void init();
    static BOOL update();
    static float getDeltaTime();
    static LONGLONG getHiPerformanceDeltaTime();

};

