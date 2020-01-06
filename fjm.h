#if !defined(FMJ_H)

#include <stdint.h>
#define KiloBytes(v) (v * 1024LL)
#define MegaBytes(v) (KiloBytes(v) * 1024LL)
#define GigaBytes(v) (MegaBytes(v) * 1024LL)
#define TeraBytes(v) (GigaBytes(v) * 1024LL)

#define U32FromPointer(pointer) ((u32)(memory_index)pointer)
#define PointerFromU32(type,value) (type*)((memory_index)value)

typedef float f32;
typedef double f64;
typedef int8_t s8;


struct GPUInfo
{
    
};





#defined FMJ_H
#endif


