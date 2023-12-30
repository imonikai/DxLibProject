#pragma once

#include "DxLib.h"

class FpsControll
{
private:
    FpsControll() = delete;

    static int FPS; //設定したいfps
    static float fps; //計算したfps
    static int measureStartTime;
    static int frameCount;
    static int calcFpsInterval; //fpsを計算するフレーム間隔

    static BOOL wait();

public:
    static void init();
    static BOOL update();
    static float getFps();
    static LONGLONG getFrameCount();

};
