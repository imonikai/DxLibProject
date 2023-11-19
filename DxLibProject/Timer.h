#pragma once
#include "DxLib.h"

class Timer {
private:
    Timer() = delete;

    static LONGLONG nowTime;
    static LONGLONG beforeFrameHiPerformanceCount;
    static float deltaTime;
    static LONGLONG fpsCheckTime;
    static int fps;
    static int fpsCounter;

public:

    static void init();
    static BOOL update();
    static float getDeltaTime();
    static void drawFps(int x, int y);
    static void drawFps(int x, int y, int fontHandle);

};

