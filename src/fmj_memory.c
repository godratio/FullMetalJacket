#include "fmj_types.h"

FMJMemoryArenaPushParams fmj_arena_push_params_default()
{
    FMJMemoryArenaPushParams result;
    result.flags = fmj_arena_push_params_flag_none;
    result.alignment = 4;
    return result;
}

FMJMemoryArenaPushParams fmj_arena_push_params_no_clear()
{
    FMJMemoryArenaPushParams result = fmj_arena_push_params_default();
    result.flags &= ~fmj_arena_push_params_flag_clear_to_zero;
    return result;
}

umm fmj_arena_get_alignment_offset(FMJMemoryArena *arena,umm alignment)
{
    if(alignment == 0)return 0;
    umm result = 0;
    umm ptr = (umm)arena->base + arena->used;
    umm mask = alignment - 1;
    if(ptr & mask)
    {
        result = alignment - (ptr & mask);
    }
    return result;
}

void* fmj_arena_push_size_(FMJMemoryArena* arena,umm size,FMJMemoryArenaPushParams params)
{
    umm offset = fmj_arena_get_alignment_offset(arena,params.alignment);
    ASSERT(arena->used + (size + offset) <= arena->size);
    if (fmj_test_flag(params.flags, fmj_arena_push_params_flag_clear_to_zero))
    {
        fmj_arena_clear_size(arena, size);
    }
    void* result = (void*)((uint8_t*)arena->base + (arena->used + offset));
    arena->used = arena->used + (size + offset);
    return result;
}

void fmj_arena_clear_size(FMJMemoryArena *arena,umm size)
{
    ASSERT(size > 0);
    size--;
    if(arena->used < size)
    {
        size = arena->used;
    }
    if(arena->used == 0)
    {
        return;
    }
    else
    {
        u8* byte = (u8*)arena->base + arena->used;
        while (size--)
        {
            *byte++ = 0;
        }
    }
}

void* fmj_arena_get_pointer(FMJMemoryArena arena)
{
    return (uint8_t*)arena.base + arena.used;
}

FMJMemoryArena fmj_arena_init(umm size, void* base)
{
    FMJMemoryArena result = {0};
    result.base = base;
    result.size = size;
    result.used = 0;
    result.temp_count = 0;
    return result;
}

FMJMemoryArena fmj_arena_allocate(umm size)
{
    u8* mem = (u8*)fmj_os_allocate(size);
    FMJMemoryArena arena = {0};
    arena = fmj_arena_init(size,mem);
    return arena;
}


