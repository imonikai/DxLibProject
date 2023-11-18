#pragma once

#include "DxLib.h"

typedef struct {

    float x, y, r;

}  Circle;


BOOL collisionCircle(Circle& c1, Circle& c2);
