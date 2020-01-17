
#include "fmj_types.h"

f2 f2_create(f32 a,f32 b)
{
    f2 result = {0};
    result.x = a;
    result.y = b;
    return result;
}

f2 f2_add(f2 a,f2 b)
{
    f2 r = {0};
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}



