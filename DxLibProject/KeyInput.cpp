#include "KeyInput.h"
#include <climits>

unsigned int KeyInput::key[256] = { 0 };

BOOL KeyInput::update()
{
    char tmpKey[256];
    if( GetHitKeyStateAll(tmpKey) == -1) return FALSE;
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) {
            key[i]++;
            key[i] = key[i] & UINT_MAX; //UINT_MAX - 1まで行ったら0になる
        }
        else {
            key[i] = 0;
        }
    }
    return TRUE;
}

unsigned int KeyInput::getKeyHit(unsigned char keyCode)
{
    return key[keyCode];
}