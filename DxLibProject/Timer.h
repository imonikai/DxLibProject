#pragma once
#include "DxLib.h"

class Timer
{
private:

    static LONGLONG nowTime;
    static LONGLONG beforeFrameHiPerformanceCount;
    static float deltaTime;
    static LONGLONG fpsCheckTime;
    static int fps;
    static int fpsCounter;
    Timer();

public:

    static void init();
    static BOOL update();
    static float getDeltaTime();
    static void drawFps(const int x, const int y);

};

