#pragma once
#include "DxLib.h"

//ゲームの操作の種類数
inline constexpr unsigned char GAMEINPUT_ACTION_NUM = 7;

inline constexpr unsigned char GAMEINPUT_UP    = 0;
inline constexpr unsigned char GAMEINPUT_DOWN  = 1;
inline constexpr unsigned char GAMEINPUT_LEFT  = 2;
inline constexpr unsigned char GAMEINPUT_RIGHT = 3;
inline constexpr unsigned char GAMEINPUT_SHOT  = 4;
inline constexpr unsigned char GAMEINPUT_SLOW  = 5;
inline constexpr unsigned char GAMEINPUT_BOMB  = 6;

class GameInput
{
private:
    GameInput() = delete;
    
    static unsigned char xinputUp;
    static unsigned char xinputDown;
    static unsigned char xinputLeft;
    static unsigned char xinputRight;
    static unsigned char xinputShot;
    static unsigned char xinputSlow;
    static unsigned char xinputBomb;

    static int inputs[GAMEINPUT_ACTION_NUM];

public:
    static BOOL init();
    static BOOL update();
    static int getInputHit(unsigned char inputCode);
    static void setUp(unsigned char xinputCode);
    static void setDown(unsigned char xinputCode);
    static void setLeft(unsigned char xinputCode);
    static void setRight(unsigned char xinputCode);
    static void setShot(unsigned char xinputCode);
    static void setSlow(unsigned char xinputCode);
    static void setBomb(unsigned char xinputCode);

};

