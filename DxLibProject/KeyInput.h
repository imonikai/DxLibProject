#pragma once

#include "DxLib.h"

class KeyInput {
private:

    static int key[];
    KeyInput() = delete;

public:

    static BOOL update();
    static int getKeyHit(unsigned char);

};
