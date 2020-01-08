#if !defined(FMJ_TYPES_H)
#include <stdint.h>

#define APIDEF

typedef float f32;
typedef double f64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uintptr_t umm;
typedef intptr_t imm;

//TODO(Ray):Use compiler intrinsic where available ie..Clang GCC MSVC
//It seems that this may get optimized out of some compilers. also annoying warning.
#define ASSERT(Expression) if(!(Expression)){*(int *)0 = 0;};
#define ARRAYCOUNT(Array) sizeof(Array) / sizeof((Array)[0])

#define FMJKILOBYTES(v) (v * 1024LL)
#define FMJMEGABYTES(v) (FMJ_KILOBYTES(v) * 1024LL)
#define FMJGIGABYTES(v) (FMJMEGABYTES(v) * 1024LL)
#define FMJTERABYTES(v) (FMJGIGABYTES(v) * 1024LL)

#define FMJU32FROMPOINTER(pointer) ((u32)(umm)pointer)
#define FMJPOINTERFROMU32(type,value) (type*)((umm)value)

enum FMJType
{
    fmj_type_string,
    fmj_type_char,
    fmj_type_f64,
    fmj_type_f32,
    fmj_type_u64,
    fmj_type_u32,
    fmj_type_u16,
    fmj_type_u8,
    fmj_type_s64,
    fmj_type_s32,
    fmj_type_s16,
    fmj_type_s8,
    fmj_type_b32,
    fmj_type_memory_index,
};

struct FMJString
{
    u32 null_terminated;
    u32 length;
    char* string;
}typedef FMJString;

APIDEF u32 fmj_string_length(FMJString* String);
APIDEF u32 fmj_char_length(char* String);

APIDEF u32 fmj_string_length_safe(FMJString* String,u32 SafetyLength);
APIDEF u32 fmj_char_length_safe(char* String,u32 SafetyLength);

struct FMJMemoryArena
{
    void* base;
    umm size;
    u32 used;
    u32 temp_count;
}typedef MemoryArena;

enum FMJMemoryArenaPushFlags
{
    PartitionFlag_None = 0x0,
    PartitionFlag_ClearToZero = 0x1,
};

struct FMJMemoryArenaPushParams
{
    u32 Flags;
    u32 Alignment;
} typedef FMJMemoryArenaPushParams;


#define PUSHARRAY(Partition,Type,push_params,Count,...) (Type*)PushSize_(Partition,sizeof(Type)*Count,push_params,## __VA_ARGS__)
#define PUSHSTRUCT(Partition,Type,push_params,...) (Type*)PushSize_(Partition,sizeof(Type),push_params,## __VA_ARGS__)
#define PUSHSIZE(Partition,Size,push_params,...) PushSize_(Partition,Size,push_params,## __VA_ARGS__)
void* PushSize_(MemoryArena*arena, umm size,FMJMemoryArenaPushParams push_params);

APIDEF FMJString fmj_string_create(char* c,MemoryArena* Memory);

APIDEF void* fmj_get_arena_pointer(MemoryArena arena);

FMJMemoryArenaPushParams fmj_push_params_no_clear();
#define FMJ_TYPE_H
#endif
