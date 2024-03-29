﻿#include "XInput.h"
#include <climits>

void XInput::updateStick()
{
    /*スティックの入力を正規化*/
    leftStickX = padState.ThumbLX / 32767.0f;
    leftStickY = padState.ThumbLY / 32767.0f;
    rightStickX = padState.ThumbRX / 32767.0f;
    rightStickY = padState.ThumbRY / 32767.0f;

    /*デッドゾーンを考慮して入力を確定する*/
    if (leftStickX < deadZone && leftStickX > -deadZone) leftStickX = 0.0f;
    if (leftStickY < deadZone && leftStickY > -deadZone) leftStickY = 0.0f;
    if (rightStickX < deadZone && rightStickX > -deadZone) rightStickX = 0.0f;
    if (rightStickY < deadZone && rightStickY > -deadZone) rightStickY = 0.0f;

    /*inputs配列を加算する*/
    /*左スティック*/
    if (leftStickX < -deadZone) inputs[MY_XINPUT_LEFTSTICK_LEFT]++;
    else inputs[MY_XINPUT_LEFTSTICK_LEFT] = 0;
    if (leftStickX > deadZone) inputs[MY_XINPUT_LEFTSTICK_RIGHT]++;
    else inputs[MY_XINPUT_LEFTSTICK_RIGHT] = 0;
    if (leftStickY > deadZone) inputs[MY_XINPUT_LEFTSTICK_UP]++;
    else inputs[MY_XINPUT_LEFTSTICK_UP] = 0;
    if (leftStickY < -deadZone) inputs[MY_XINPUT_LEFTSTICK_DOWN]++;
    else inputs[MY_XINPUT_LEFTSTICK_DOWN] = 0;
    /*右スティック*/
    if (rightStickX < -deadZone) inputs[MY_XINPUT_RIGHTSTICK_LEFT]++;
    else inputs[MY_XINPUT_RIGHTSTICK_LEFT] = 0;
    if (rightStickX > deadZone) inputs[MY_XINPUT_RIGHTSTICK_RIGHT]++;
    else inputs[MY_XINPUT_RIGHTSTICK_RIGHT] = 0;
    if (rightStickY > deadZone) inputs[MY_XINPUT_RIGHTSTICK_UP]++;
    else inputs[MY_XINPUT_RIGHTSTICK_UP] = 0;
    if (rightStickY < -deadZone) inputs[MY_XINPUT_RIGHTSTICK_DOWN]++;
    else inputs[MY_XINPUT_RIGHTSTICK_DOWN] = 0;
}

void XInput::updateTrigger()
{
    if (padState.LeftTrigger > triggerActionPoint)
        inputs[MY_XINPUT_LEFTTRIGGER]++;
    else inputs[MY_XINPUT_LEFTTRIGGER] = 0;
    if (padState.RightTrigger > triggerActionPoint)
        inputs[MY_XINPUT_RIGHTTRIGGER]++;
    else inputs[MY_XINPUT_RIGHTTRIGGER] = 0;
}


BOOL XInput::init(int padNumber)
{
    if (padNumber < 1 || padNumber > 4)
        XInput::padNumber = 1;

    return update();
}

BOOL XInput::update()
{
    int result = GetJoypadXInputState(padNumber, &padState);
    if (result == 0)
    {
        /*XINPUT_STATE構造体のButtonsの範囲をinputsに反映させる*/
        for (int i = 0; i < 16; i++)
        {
            if (padState.Buttons[i] == 1)
                inputs[i]++;
            else
                inputs[i] = 0;
        }
        /*スティックとトリガーをinputsに反映*/
        updateStick();
        updateTrigger();

        /*inputsのint範囲超え対策*/
        for (int i = 0; i < MY_XINPUT_INPUT_NUM; i++)
        {
            if (inputs[i] == INT_MAX)
                inputs[i] = 2;
        }
    }
    /*デバッグ*/
    /*
    clsDx();
    printfDx(_T("leftStickX = % f, leftStickY = % f\n"), leftStickX, leftStickY);
    printfDx(_T("rightStickX = %f, rightStickY = %f\n"), rightStickX, rightStickY);
    printfDx(_T("leftTrigger = %d rightTrigger = %d\n"), padState.LeftTrigger, padState.RightTrigger);
    for (int i = 0; i < MY_XINPUT_INPUT_NUM; i++)
    {
        printfDx(_T("inputs[%d] = %d\n"), i, inputs[i]);
    }
    */
    return TRUE;
}

int XInput::getInputHit(unsigned char inputCode)
{
    if (inputCode < 0 || inputCode >= MY_XINPUT_INPUT_NUM) return -1;
    return inputs[inputCode];
}

void XInput::setDeadZone(float newDeadZone)
{
    deadZone = newDeadZone;
}

void XInput::setTriggerActionPoint(unsigned char point)
{
    triggerActionPoint = point;
}
