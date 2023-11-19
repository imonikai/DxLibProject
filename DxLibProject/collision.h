#pragma once

#include "DxLib.h"

struct Circle {

    float x, y, r;

};


BOOL collisionCircle(Circle&, Circle&);
