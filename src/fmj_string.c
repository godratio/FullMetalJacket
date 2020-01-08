
#include "fmj_types.h"

APIDEF u32 fmj_string_length(FMJString* s)
{
    ASSERT(s->null_terminated);
    u32 result = 0;
    char* at = s->string;
    while(*at)
    {
        result++;
        at++;
    }
    s->length = result;
    return result;    
}

APIDEF u32 fmj_char_length(char* s)
{
    u32 result = 0;
    char* at = s;
    while(*at)
    {
        result++;
        at++;
    }
    return result;
}

APIDEF u32 fmj_string_length_safe(FMJString* s,u32 safe_length)
{
    ASSERT(s->null_terminated);
    u32 result = 0;
    char* at = s->string;
    while(*at)
    {
        result++;
        at++;
        if(result > safe_length)
        {
            break;
        }
    }
    s->length = result;
    return result;
}

APIDEF u32 fmj_char_length_safe(char* s,u32 safe_length)
{
    u32 result = 0;
    char* at = s;
    while(*at)
    {
        result++;
        at++;
        if(result > safe_length)
        {
            break;
        }
    }
    return result;
}

APIDEF FMJString fmj_string_null_terminate(FMJString str,MemoryArena* arena)
{
    char *term_ptr = (char*)PUSHSIZE(arena,1,fmj_push_params_no_clear());
    *term_ptr = '\0';
    str.null_terminated = 0;
    return str;
}

APIDEF FMJString fmj_string_create_(char* c,MemoryArena* arena)
{
    FMJString result = {};
    char* at = c;
    void* start = fmj_get_arena_pointer(*arena);
	while (*at)
    {
        char * ptr = (char*)PUSHSIZE(arena,1,fmj_push_params_no_clear());
        *ptr = *at;
        result.length++;
        at++;
    }
    result.string = (char*)start;
    return fmj_string_null_terminate(result,arena);
    return result;
}


