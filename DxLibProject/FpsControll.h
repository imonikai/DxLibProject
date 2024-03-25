#pragma once

#include "DxLib.h"

class FpsControll
{
private:
    FpsControll() = delete;

    static inline int FPS; //設定したいfps
    static inline float fps; //計算したfps
    static inline int measureStartTime;
    static inline int frameCount;
    static inline int calcFpsInterval; //fpsを計算するフレーム間隔

    static BOOL wait();

public:
    static void init(int fps = 60);
    static void setFps(int fps);
    static BOOL update();
    static float getFps();
    static LONGLONG getFrameCount();

};
