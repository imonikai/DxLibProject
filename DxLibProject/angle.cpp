#include "angle.h"

float rad(float degree)
{
    return (degree * 3.14159f / 180.0f);
}

float normalizeAngle(float rad)
{
    if (rad < (3.14159f * 2))
        return rad;
    else
        rad -= ((3.14159f * 2));

    return rad;
}
