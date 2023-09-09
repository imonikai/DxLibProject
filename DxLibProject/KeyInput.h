#pragma once

#include "DxLib.h"

class KeyInput
{
private:

    static unsigned int key[];
    KeyInput() = delete;

public:

    static BOOL update();
    static unsigned int getKeyHit(unsigned char);

};