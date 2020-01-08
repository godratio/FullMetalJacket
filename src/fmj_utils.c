#include "fmj_types.h"

bool fmj_test_flag(u32 flag, u32 test)
{
    if ((flag & test) == test)
    {
        return true;
    }
    return false;
}

