#include "collision.h"

BOOL collisionCircle(Circle c1, Circle c2)
{
    float distance2 = (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
    float rSum2 = (c1.r + c2.r) * (c1.r + c2.r);

    if (distance2 <= rSum2)
        return TRUE;
    else
        return FALSE;
}
