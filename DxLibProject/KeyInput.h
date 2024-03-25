#pragma once

#include "DxLib.h"

class KeyInput {
private:
    KeyInput() = delete;

    static inline int key[256] = { 0 };

public:

    static BOOL update();
    static int getKeyHit(unsigned char);

};
