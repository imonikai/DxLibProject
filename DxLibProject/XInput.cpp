#include "XInput.h"
#include <climits>

XINPUT_STATE XInput::padState;
int XInput::padNumber = 1;
unsigned char XInput::triggerActionPoint = 0;
float XInput::deadZone = 0.35f;
float XInput::leftStickX;
float XInput::leftStickY;
float XInput::rightStickX;
float XInput::rightStickY;
int XInput::inputs[MY_XINPUT_INPUT_NUM] = { 0 };

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
    if (leftStickX < -deadZone) inputs[MY_XINPUT_LEFT_STICK_LEFT]++;
    else inputs[MY_XINPUT_LEFT_STICK_LEFT] = 0;
    if (leftStickX > deadZone) inputs[MY_XINPUT_LEFT_STICK_RIGHT]++;
    else inputs[MY_XINPUT_LEFT_STICK_RIGHT] = 0;
    if (leftStickY > deadZone) inputs[MY_XINPUT_LEFT_STICK_UP]++;
    else inputs[MY_XINPUT_LEFT_STICK_UP] = 0;
    if (leftStickY < -deadZone) inputs[MY_XINPUT_LEFT_STICK_DOWN]++;
    else inputs[MY_XINPUT_LEFT_STICK_DOWN] = 0;
    /*右スティック*/
    if (rightStickX < -deadZone) inputs[MY_XINPUT_RIGHT_STICK_LEFT]++;
    else inputs[MY_XINPUT_RIGHT_STICK_LEFT] = 0;
    if (rightStickX > deadZone) inputs[MY_XINPUT_RIGHT_STICK_RIGHT]++;
    else inputs[MY_XINPUT_RIGHT_STICK_RIGHT] = 0;
    if (rightStickY > deadZone) inputs[MY_XINPUT_RIGHT_STICK_UP]++;
    else inputs[MY_XINPUT_RIGHT_STICK_UP] = 0;
    if (rightStickY < -deadZone) inputs[MY_XINPUT_RIGHT_STICK_DOWN]++;
    else inputs[MY_XINPUT_RIGHT_STICK_DOWN] = 0;
}

void XInput::updateTrigger()
{
    if (padState.LeftTrigger > triggerActionPoint)
        inputs[MY_XINPUT_LEFT_TRIGGER]++;
    else inputs[MY_XINPUT_LEFT_TRIGGER] = 0;
    if (padState.RightTrigger > triggerActionPoint)
        inputs[MY_XINPUT_RIGHT_TRIGGER]++;
    else inputs[MY_XINPUT_RIGHT_TRIGGER] = 0;
}


BOOL XInput::init(const int _padNumber)
{
    if (_padNumber < 1 || _padNumber > 4) padNumber = 1;

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
            {
                inputs[i]++;
            }
            else
            {
                inputs[i] = 0;
            }
        }
        /*スティックとトリガーをinputsに反映*/
        updateStick();
        updateTrigger();

        /*inputsのint範囲超え対策*/
        for (int i = 0; i < MY_XINPUT_INPUT_NUM; i++)
        {
            inputs[i] %= INT_MAX;
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

int XInput::getInputHit(const unsigned char inputCode)
{
    if (inputCode < 0 || inputCode > MY_XINPUT_INPUT_NUM) return -1;
    return inputs[inputCode];
}

void XInput::setDeadZone(const float newDeadZone)
{
    deadZone = newDeadZone;
}

void XInput::setTriggerActionPoint(const unsigned char point)
{
    triggerActionPoint = point;
}