﻿#pragma once

#include "DxLib.h"

/*XINPUTの入力取得のための追加定数（DXライブラリの仕様変更があるかもしれないのでMY_をつけておく)*/
#define MY_XINPUT_LEFTSTICK_UP (16)
#define MY_XINPUT_LEFTSTICK_DOWN (17)
#define MY_XINPUT_LEFTSTICK_LEFT (18)
#define MY_XINPUT_LEFTSTICK_RIGHT (19)
#define MY_XINPUT_RIGHTSTICK_UP (20)
#define MY_XINPUT_RIGHTSTICK_DOWN (21)
#define MY_XINPUT_RIGHTSTICK_LEFT (22)
#define MY_XINPUT_RIGHTSTICK_RIGHT (23)
#define MY_XINPUT_LEFTTRIGGER (24)
#define MY_XINPUT_RIGHTTRIGGER (25)
#define MY_XINPUT_INPUT_NUM (26)

class XInput {
private:
    XInput() = delete;

    /* パッドの情報更新用変数 */
    static inline XINPUT_STATE padState; //パッドの情報を取得する構造体
    static inline int padNumber; //パッドの番号
    static inline unsigned char triggerActionPoint; //トリガーを反応させる値
    static inline float deadZone; //スティックのデッドゾーン -1.0 ~ 1.0
    static inline float leftStickX; //正規化された左スティックのx -1.0 ~ 1.0
    static inline float leftStickY; //正規化された左スティックのy -1.0 ~ 1.0
    static inline float rightStickX; //正規化された右スティックのx -1.0 ~ 1.0
    static inline float rightStickY; //正規化された右スティックのy -1.0 ~ 1.0

    /* パッドの情報蓄積用変数（KeyInutと同じような感じで使うための変数) */
    static inline int inputs[] = { 0 };


    static void updateStick();
    static void updateTrigger();

public:

    static BOOL init(int padNumber);
    static BOOL update();
    static int getInputHit(unsigned char inputCode);
    static void setDeadZone(float newDeadZone);
    static void setTriggerActionPoint(unsigned char point);

};

