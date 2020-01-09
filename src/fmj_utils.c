#include "fmj_types.h"

bool fmj_test_flag(u32 flag, u32 test)
{
    if ((flag & test) == test)
    {
        return true;
    }
    return false;
}

void fmj_clear_to_zero(void* ptr,umm size)
{
    for (u32 byte_index = 0; byte_index < size; ++byte_index)
    {
        uint8_t* byte = (uint8_t*)ptr + byte_index;
        *byte = 0;
    }
}

