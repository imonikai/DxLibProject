#pragma once

#include "DxLib.h"

class KeyInput {
private:
    KeyInput() = delete;

    static int key[];

public:

    static BOOL update();
    static int getKeyHit(unsigned char);

};
