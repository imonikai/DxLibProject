#include "GameInput.h"
#include "KeyInput.h"
#include "XInput.h"
#include <climits>

unsigned char GameInput::xinputUp;
unsigned char GameInput::xinputDown;
unsigned char GameInput::xinputLeft;
unsigned char GameInput::xinputRight;
unsigned char GameInput::xinputShot;
unsigned char GameInput::xinputSlow;
unsigned char GameInput::xinputBomb;

int GameInput::inputs[GAMEINPUT_ACTION_NUM] = { 0 };

BOOL GameInput::init()
{
    XInput::init(DX_INPUT_PAD1);

    setUp(MY_XINPUT_LEFTSTICK_UP);
    setDown(MY_XINPUT_LEFTSTICK_DOWN);
    setLeft(MY_XINPUT_LEFTSTICK_LEFT);
    setRight(MY_XINPUT_LEFTSTICK_RIGHT);
    setShot(XINPUT_BUTTON_X);
    setSlow(XINPUT_BUTTON_A);
    setBomb(XINPUT_BUTTON_Y);

    return TRUE;
}

BOOL GameInput::update()
{
    KeyInput::update();
    XInput::update();

    /* 上 */
    if (KeyInput::getKeyHit(KEY_INPUT_UP)
        || XInput::getInputHit(xinputUp))
        inputs[GAMEINPUT_UP]++;
    else
        inputs[GAMEINPUT_UP] = 0;

    /* 下 */
    if (KeyInput::getKeyHit(KEY_INPUT_DOWN)
        || XInput::getInputHit(xinputDown))
        inputs[GAMEINPUT_DOWN]++;
    else
        inputs[GAMEINPUT_DOWN] = 0;

    /* 左 */
    if (KeyInput::getKeyHit(KEY_INPUT_LEFT)
        || XInput::getInputHit(xinputLeft))
        inputs[GAMEINPUT_LEFT]++;
    else
        inputs[GAMEINPUT_LEFT] = 0;

    /* 右 */
    if (KeyInput::getKeyHit(KEY_INPUT_RIGHT)
        || XInput::getInputHit(xinputRight))
        inputs[GAMEINPUT_RIGHT]++;
    else
        inputs[GAMEINPUT_RIGHT] = 0;

    /* ショット */
    if (KeyInput::getKeyHit(KEY_INPUT_Z)
        || XInput::getInputHit(xinputShot))
        inputs[GAMEINPUT_SHOT]++;
    else
        inputs[GAMEINPUT_SHOT] = 0;

    /* スロー */
    if (KeyInput::getKeyHit(KEY_INPUT_LSHIFT)
        || XInput::getInputHit(xinputSlow))
        inputs[GAMEINPUT_SLOW]++;
    else
        inputs[GAMEINPUT_SLOW] = 0;

    /* ボム */
    if (KeyInput::getKeyHit(KEY_INPUT_X)
        || XInput::getInputHit(xinputBomb))
        inputs[GAMEINPUT_BOMB]++;
    else
        inputs[GAMEINPUT_BOMB] = 0;

    /* 範囲超え対策 */
    for (int i = 0; i < GAMEINPUT_ACTION_NUM; i++)
    {
        if (inputs[i] == INT_MAX)
            inputs[i] = 2;
    }

    return TRUE;
}

int GameInput::getInputHit(unsigned char inputCode)
{
    return inputs[inputCode];
}

void GameInput::setUp(unsigned char xinputCode)
{
    xinputUp = xinputCode;
}

void GameInput::setDown(unsigned char xinputCode)
{
    xinputDown = xinputCode;
}

void GameInput::setLeft(unsigned char xinputCode)
{
    xinputLeft = xinputCode;
}

void GameInput::setRight(unsigned char xinputCode)
{
    xinputRight = xinputCode;
}

void GameInput::setShot(unsigned char xinputCode)
{
    xinputShot = xinputCode;
}

void GameInput::setSlow(unsigned char xinputCode)
{
    xinputSlow = xinputCode;
}

void GameInput::setBomb(unsigned char xinputCode)
{
    xinputBomb = xinputCode;
}
