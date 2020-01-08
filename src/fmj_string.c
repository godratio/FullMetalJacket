
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

APIDEF u32 fmj_string_char_length(char* s)
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

APIDEF u32 fmj_string_char_length_safe(char* s,u32 safe_length)
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

APIDEF FMJString fmj_string_null_terminate(FMJString str,FMJMemoryArena* arena)
{
    FMJMemoryArenaPushParams pp = fmj_arena_push_params_no_clear();
    pp.alignment = 1;
    char *term_ptr = (char*)PUSHSIZE(arena,1,pp);
    *term_ptr = '\0';
    str.null_terminated = true;
    return str;
}

APIDEF FMJString fmj_string_create(char* c,FMJMemoryArena* arena)
{
    FMJString result = {0};
    char* at = c;
    void* start = fmj_arena_get_pointer(*arena);
    FMJMemoryArenaPushParams pp = fmj_arena_push_params_no_clear();
    pp.alignment = 1;
	while (*at)
    {
        char * ptr = (char*)PUSHSIZE(arena,1,pp);
        *ptr = *at;
        result.length++;
        at++;
    }
    result.string = (char*)start;
    return fmj_string_null_terminate(result,arena);
}

APIDEF FMJString fmj_string_create_from_ptr(char* start,char* end,FMJMemoryArena* arena)
{
    FMJString result = {0};
    char* at = start;
    void* start_ptr = fmj_arena_get_pointer(*arena);
    char* string_ptr = 0;
    FMJMemoryArenaPushParams pp = fmj_arena_push_params_no_clear();
    pp.alignment = 1;    
    while (at != end)
    {
        string_ptr = (char*)PUSHSIZE(arena, 1,pp);
        *string_ptr = *at;
        result.length++;
        at++;
    }
    result.string = (char*)start_ptr;
    return fmj_string_null_terminate(result,arena);
}

APIDEF FMJString fmj_string_create_from_length(char* start,umm length,FMJMemoryArena* arena)
{
    FMJString result = {0};
    const char* at = start;
    void* start_ptr = fmj_arena_get_pointer(*arena);
    char* string_ptr = 0;
    u32 itr = 0;
    FMJMemoryArenaPushParams pp = fmj_arena_push_params_no_clear();
    pp.alignment = 1;        
    while (itr < length)
    {
        string_ptr = (char*)PUSHSIZE(arena,1,pp);
        *string_ptr = *at;
        result.length++;
        at++;
        itr++;
    }
    result.string = (char*)start_ptr;
    return fmj_string_null_terminate(result,arena);    
}

APIDEF bool fmj_string_cmp(FMJString a, FMJString b)
{
    if (a.null_terminated && b.null_terminated)
    {
        char* a_ptr = a.string;
        char* b_ptr = b.string;
        while (*a_ptr && *b_ptr)
        {
            if (*a_ptr != *b_ptr)
                return false;
            a_ptr++;b_ptr++;
        }
    }
    else
    {
        char* a_ptr = a.string;
        char* b_ptr = b.string;
        u32 max_itr = (a.length > b.length) ? a.length : b.length;
        for(u32 idx = 0;idx < max_itr;++idx)
        {
            if (*a_ptr != *b_ptr)
                return false;
            a_ptr++; b_ptr++;
        }
    }
    return true;
}

APIDEF bool fmj_string_cmp_char(FMJString a,const char* b)
{
    char* a_ptr = a.string;
    const char* b_ptr = b;
    u32 max_itr = fmax(a.length,fmj_string_char_length((char*)b));
    for(u32 idx = 0;idx < max_itr;++idx)
    {
        //TODO(Ray):Need to check logic here for string where B is longer than A
        if (*a_ptr != *b_ptr)
            return false;
        a_ptr++; b_ptr++;
    }
    return true;
}

APIDEF bool fmj_string_cmp_char_to_char(const char* a,const char* b,u32 max_itr)
{
    const char* a_ptr = a;
    const char* b_ptr = b;
    for(u32 idx = 0;idx < max_itr;++idx)
    {
        if(*a_ptr == '\0' || *b_ptr == '\0')break;
        if (*a_ptr != *b_ptr)
            return false;
        a_ptr++; b_ptr++;
    }
    return true;
}

