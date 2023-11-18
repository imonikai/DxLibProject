#pragma once

#include "DxLib.h"

/*XINPUTの入力取得のための追加定数（DXライブラリの仕様変更があるかもしれないのでMY_をつけておく)*/
#define MY_XINPUT_LEFT_STICK_UP (16)
#define MY_XINPUT_LEFT_STICK_DOWN (17)
#define MY_XINPUT_LEFT_STICK_LEFT (18)
#define MY_XINPUT_LEFT_STICK_RIGHT (19)
#define MY_XINPUT_RIGHT_STICK_UP (20)
#define MY_XINPUT_RIGHT_STICK_DOWN (21)
#define MY_XINPUT_RIGHT_STICK_LEFT (22)
#define MY_XINPUT_RIGHT_STICK_RIGHT (23)
#define MY_XINPUT_LEFT_TRIGGER (24)
#define MY_XINPUT_RIGHT_TRIGGER (25)
#define MY_XINPUT_INPUT_NUM (26)

class XInput {
private:

    /* パッドの情報更新用変数 */
    static XINPUT_STATE padState; //パッドの情報を取得する構造体
    static int padNumber; //パッドの番号
    static unsigned char triggerActionPoint; //トリガーを反応させる値
    static float deadZone; //スティックのデッドゾーン -1.0 ~ 1.0
    static float leftStickX; //正規化された左スティックのx -1.0 ~ 1.0
    static float leftStickY; //正規化された左スティックのy -1.0 ~ 1.0
    static float rightStickX; //正規化された右スティックのx -1.0 ~ 1.0
    static float rightStickY; //正規化された右スティックのy -1.0 ~ 1.0

    /* パッドの情報蓄積用変数（KeyInutと同じような感じで使うための変数) */
    static int inputs[];


    static void updateStick();
    static void updateTrigger();
    XInput() = delete;

public:

    static BOOL init(const int _padNumber);
    static BOOL update();
    static int getInputHit(const unsigned char inputCode);
    static void setDeadZone(const float newDeadZone);
    static void setTriggerActionPoint(const unsigned char point);

};

