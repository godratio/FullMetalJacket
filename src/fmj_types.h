
#if !defined(FMJ_TYPES_H)
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "external/meow_hash/meow_hash_x64_aesni.h"

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
#define FMJMEGABYTES(v) (FMJKILOBYTES(v) * 1024LL)
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
//OS API
void* fmj_os_allocate(umm size);
void fmj_os_deallocate(void* mem,umm size);
//End OSAPI

//ENDI OS API

//Defines and Magic Numbers

//BEGIN STRINGS API
#define MAX_FILENAME_LENGTH 50
#define MAX_FILE_EXTENSION_LENGTH 3
//END STRINGS API

//TYPE DECLARATIONS

//MEMORY API
void fmj_memory_copy(void* dst,void* src,umm size);

struct FMJMemoryArena
{
    void* base;
    void* aligned_base;
    umm size;
    u32 used;
    u32 temp_count;
}typedef FMJMemoryArena;

enum FMJMemoryArenaPushFlags
{
    fmj_arena_push_params_flag_none = 0x0,
    fmj_arena_push_params_flag_clear_to_zero = 0x1,
};

struct FMJMemoryArenaPushParams
{
    u32 flags;
    u32 alignment;
} typedef FMJMemoryArenaPushParams;

#define PUSHARRAY(Partition,Type,push_params,Count,...) (Type*)fmj_arena_push_size_(Partition,sizeof(Type)*Count,push_params,## __VA_ARGS__)
#define PUSHSTRUCT(Partition,Type,push_params,...) (Type*)fmj_arena_push_size_(Partition,sizeof(Type),push_params,## __VA_ARGS__)
#define PUSHSIZE(Partition,Size,push_params,...) fmj_arena_push_size_(Partition,Size,push_params,## __VA_ARGS__)
void* fmj_arena_push_size_(FMJMemoryArena* arena,umm size,FMJMemoryArenaPushParams params);
void fmj_arena_clear_size(FMJMemoryArena *arena,umm size);
umm fmj_arena_get_alignment_offset(FMJMemoryArena *arena,umm alignment);
    
void* fmj_arena_get_pointer(FMJMemoryArena arena);
FMJMemoryArenaPushParams fmj_arena_push_params_default();
FMJMemoryArenaPushParams fmj_arena_push_params_no_clear();
FMJMemoryArena fmj_arena_init(umm size, void* base);
FMJMemoryArena fmj_arena_allocate(umm size);

FMJMemoryArena fmj_arena_init(umm size, void* base);
FMJMemoryArena fmj_arena_allocate(umm size);

void fmj_arena_deallocate(FMJMemoryArena *arena, bool clear_mem_to_zero);
void fmj_arena_free(FMJMemoryArena* arena);
//END MEMORY API

//Strings API
struct FMJString
{
    bool null_terminated;
    u32 length;
    char* string;
}typedef FMJString;

//unsafe
APIDEF u32 fmj_string_length(FMJString* String);
APIDEF u32 fmj_string_char_length(char* String);
//safe version
APIDEF u32 fmj_string_length_safe(FMJString* String,u32 SafetyLength);
APIDEF u32 fmj_string_char_length_safe(char* String,u32 SafetyLength);
//init
APIDEF FMJString fmj_string_create(char* c,FMJMemoryArena* Memory);
APIDEF FMJString fmj_string_create_from_ptr(char* start,char* end,FMJMemoryArena* arena);
APIDEF FMJString fmj_string_create_from_length(char* start,umm length,FMJMemoryArena* arena);

APIDEF bool fmj_string_cmp(FMJString a, FMJString b);
APIDEF bool fmj_string_cmp_char(FMJString a,const char* b);
APIDEF bool fmj_string_cmp_char_to_char(const char* a,const char* b,u32 max_itr);

APIDEF FMJString fmj_string_get_filename(char* path_with_filename,u64 length,FMJMemoryArena* arena);
APIDEF FMJString fmj_string_get_extension(FMJString file_name_or_path_with_extension,FMJMemoryArena *arena,bool keep_file_extension_delimeter);
APIDEF FMJString fmj_string_strip_extension(FMJString file_name_or_path_with_extension,FMJMemoryArena *arena);
APIDEF FMJString fmj_string_strip_and_output_extension(FMJString* file_name_or_path_with_extension,FMJString* ext,FMJMemoryArena *arena,bool keep_file_extension_delimeter);
APIDEF FMJString fmj_string_pad_right(FMJString String,char PadChar,u32 PadAmount,FMJMemoryArena* Memory);
APIDEF FMJString fmj_string_enforce_min_size(FMJString string,u32 min_size,FMJMemoryArena* arena);
//TODO(Ray)://NOTE(ray):Both string allocs are put into the same arena which may not what we want all the time..
//in the future look at a convient way to split the allocs.
//the temp allocced string here should be just thrown away not appeneded to the passed in memory.
#define fmj_string_append_char_to_char(front,back,arena) fmj_string_append(fmj_string_create(front,arena),fmj_string_create(back,arena),arena)
#define fmj_string_append_char(front,back,arena) fmj_string_append(front,fmj_string_create(back,arena),arena)
APIDEF FMJString fmj_string_append(FMJString front,FMJString back,FMJMemoryArena* arena);
//End Strings API

//Begin Buffers/Collections/DataStructures API
struct FMJFixedBuffer
{
    void* base;
	umm capacity;
    umm total_size;
	umm unit_size;
	umm count;
	u32 at_index;
	int start_at;
    u32 alignment;    
    FMJMemoryArena mem_arena;
} typedef FMJFixedBuffer;

#define fmj_fixed_buffer_get_ptr(type,buffer,index) (type*)fmj_fixed_buffer_get_(buffer,index);
#define fmj_fixed_buffer_get(type,buffer,index) *(type*)fmj_fixed_buffer_get_(buffer,index);

#define fmj_fixed_buffer_get_any(type,buffer,index) (type*)fmj_fixed_buffer_get_any_(buffer,index);
FMJFixedBuffer fmj_fixed_buffer_init(umm capacity,umm unit_size,u32 alignment);
u64 fmj_fixed_buffer_push(FMJFixedBuffer* buffer, void* element);
void* fmj_fixed_buffer_get_(FMJFixedBuffer* buffer, u64 index);

//NOTE(ray):main difference is that any can access any where inside the buffer
//regardless of push count but based on capacity.
void* fmj_fixed_buffer_get_any_(FMJFixedBuffer* buffer, u64 index);
void fmj_fixed_buffer_clear(FMJFixedBuffer *buffer);
void fmj_fixed_buffer_free(FMJFixedBuffer *buffer);
void fmj_fixed_buffer_pop(FMJFixedBuffer* buffer);


//Stretchy 
struct FMJStretchBuffer
{
    FMJFixedBuffer fixed;
    f32 resize_ratio;//0.1 10% 1 100% default is 50% or 1/2 resizing
    u32 alignment_offset;
    u64 borrow_count;
} typedef FMJStretchBuffer;

FMJStretchBuffer fmj_stretch_buffer_init(umm capacity,umm unit_size,u32 alignment);
u64 fmj_stretch_buffer_push(FMJStretchBuffer* buffer, void* element);

#define fmj_stretch_buffer_check_out(type,buffer,index) (type*)fmj_stretch_buffer_checkout_ptr_(buffer,index);
#define fmj_stretch_buffer_get(type,buffer,index) *(type*)fmj_stretch_buffer_get_(buffer,index);
void* fmj_stretch_buffer_get_any_(FMJStretchBuffer* buffer,u64 index);
void* fmj_stretch_buffer_checkout_ptr_(FMJStretchBuffer* buffer,u64 index);
void fmj_stretch_buffer_check_in(FMJStretchBuffer* buffer);
 
//WARNING(ray):You get no protection when using this function.
void* fmj_stretch_buffer_get_(FMJStretchBuffer* buffer,u64 index);
void fmj_fixed_buffer_clear_item(FMJFixedBuffer* b,u64 i);
void fmj_stretch_buffer_clear_item(FMJStretchBuffer* s,u64 i);
void fmj_stretch_buffer_clear(FMJStretchBuffer *b);
void fmj_stretch_buffer_free(FMJStretchBuffer *b);
void fmj_stretch_buffer_pop(FMJStretchBuffer* b);
//End Buffer/Collections/DataStructures API

//BEGIN HASHTABLE
struct FMJHashKeyEntry
{
	u64 value_index;
    u64 backing_index;
    bool indexed;//TODO(Ray):Try to get rid of this flag laters
    bool tombstoned;//TODO(Ray):Indexed and tombstoned should be in a state index variable
	u32 collision_count;
    int collision_head_index;
    struct FMJHashCollisionEntry* collision_head;
} typedef FMJHashKeyEntry;

struct FMJHashValueEntry
{
	void* value;
} typedef FMJHashValueEntry;

struct FMJHashCollisionEntry
{
    FMJHashKeyEntry key;
    FMJHashValueEntry value;
    umm index;
    int next_index;
} typedef FMJHashCollisionEntry;

struct FMJHashAddElementResult
{
    bool is_succeed;
    u64 result;
} typedef FMJHashAddElementResult;

struct FMJHashTable
{
    FMJStretchBuffer key_backing_array;
	FMJFixedBuffer keys;
	FMJFixedBuffer values;
    FMJStretchBuffer collisions;
    FMJStretchBuffer collision_free_list;
    u64 table_size;
    u64 collision_count;
    u64 key_size;
    u64 key_value;
} typedef FMJHashTable;

#define fmj_hashtable_init(start_count,key_type) fmj_hashtable_init_(start_count,sizeof(key_type))
FMJHashTable fmj_hashtable_init_(u64 start_count,u64 key_size);
u64 fmj_hashtable_meow_hash_func(void* buffer,uint64_t size);
u64 fmj_hashtable_hash_func(FMJHashTable* h_table,void* buffer,uint64_t size);
FMJHashAddElementResult fmj_hashtable_add(FMJHashTable* h_table,void* key,u64 key_size,void* element);
#define fmj_hashtable_get(type,table,in,size) (type*)fmj_hashtable_get_(table,in,size)
void* fmj_hashtable_get_(FMJHashTable* h_table,void* key,u64 size);
void fmj_hashtable_remove(FMJHashTable* h_table,void* key);
bool fmj_hashtable_contains(FMJHashTable* h_table,void* key,uint64_t size);
//END HASHTABLE

//BEGIN ANYTHING CACHE
struct AnyCache
{
    FMJHashTable hash;
    umm key_size;
    bool is_init;
    FMJStretchBuffer anythings;
    bool is_using_free_list;
    FMJStretchBuffer free_list;
} typedef AnyCache;

#define fmj_anycache_get(type,cache,key) *(type*)fmj_anycache_get_(cache,key)
#define fmj_anycache_checkout(type,cache,key) (type*)fmj_anycache_get_(cache,key)
//Returns the first free element null if it does not exist
#define fmj_anycache_checkout_first_free(type,cache) (type*)fmj_anycache_checkout_first_free_(cache);
#define fmj_anycache_checkout_first_free_with_predicate(type,cache,predicate) (type*)fmj_anycache_checkout_first_free_with_predicate_(&cache,predicate);

AnyCache fmj_anycache_init(u32 max_hash_states,umm size_of_thing,umm size_of_key,bool is_using_free_list);
bool fmj_anycache_exist(AnyCache* cache,void* key);
//Returns key for later retrival
bool fmj_anycache_add(AnyCache* cache,void* key,void* thing);
bool fmj_anycache_add_to_free_list(AnyCache* cache,void* key,void* thing);
void fmj_anycache_remove(AnyCache* cache,void* key);
void fmj_anycache_remove_free_list(AnyCache* cache,void* key);
void* fmj_anycache_get_(AnyCache* cache,void* key);
void* fmj_anycache_checkout_(AnyCache* cache,void* key);
void fmj_anycache_checkin_(AnyCache* cache,void* key);
void fmj_anycache_reset(AnyCache* cache);
void* fmj_anycache_checkout_first_free_(AnyCache* cache);
void* fmj_anycache_checkout_first_free_with_predicate_(AnyCache* cache,bool (*predicate)(void*));
//END ANYTHING CACHE

//BEGIN FILE API
struct FMJFileReadResult
{
	umm content_size;
	void* content;
}typedef FMJFileReadResult;

struct FMJFileDirInfoResult
{
	FMJFixedBuffer files;
}typedef FMJFileDirInfoResult;

struct FMJFileInfo
{
	void* file;
	FMJString name;
	umm file_size;
	u32 file_count;
} typedef FMJFileInfo;

struct FMJFileHandle
{
	FILE* file;
} typedef FMJFileHandle;

FMJFileDirInfoResult fmj_file_platform_get_all_files_in_dir(char* path, FMJMemoryArena* arena);
FMJFileReadResult fmj_file_platform_read_entire_file(char* file_name);
//END FILE API

//BEGIN THREAD API
struct FMJThreadSemaphore
{
    void* state;
} typedef FMJThreadSemaphore;

struct FMJThread
{
    u64 id;
} typedef FMJThread;

struct FMJTicketMutex
{
    s64 volatile ticket;
    s64 volatile serving;
} typedef FMJTicketMutex;

//TODO(ray):decide later what we will do about inlining
#define FMJ_ATOMICS_INLINE //__forceinline

u64 fmj_thread_get_cpu_core_count();
u64 fmj_thread_get_thread_id();
FMJThread fmj_thread_create(void*(*func)(void*),void* func_data);
FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_compare_exchange64(s64 volatile *value,s64 new_value,s64 expected_value);
FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_increment64(s64 volatile *value);
FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_decrement64(s64 volatile *value);
FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_add64(s64 volatile *value,s64 amount);
FMJ_ATOMICS_INLINE void fmj_thread_begin_ticket_mutex(FMJTicketMutex* mutex);
FMJ_ATOMICS_INLINE void fmj_thread_end_ticket_mutex(FMJTicketMutex* mutex);
FMJThreadSemaphore fmj_thread_create_semaphore(u64 value); 
//END THREAD API

//BEGIN MATH API

union f2
{
    struct
    {
        f32 x;
        f32 y;
    };
    struct
    {
        f32 r;
        f32 b;
    };
    struct
    {
        f32 s;
        f32 t;
    };
    struct
    {
        f32 u;
        f32 v;
    };
    struct
    {
        f32 left;
        f32 right;
    };
    struct
    {
        f32 width;
        f32 height;
    };
    struct
    {
        f32 xy[2];  
    };
    
} typedef f2;

union f3
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 b;
    };
    struct
    {
        f32 xyz[3];  
    };
    struct
    {
        f32 rgb[3];  
    };
} typedef f3;

union f4
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
    struct
    {
        f32 left;
        f32 top;
        f32 right;
        f32 bottom;
    };
    struct
    {
        f32 xyzw[4];  
    };
    struct
    {
        f32 rgba[4];  
    };
} typedef f4;

typedef f4 quaternion;

struct f3x3
{
    f3 c0;
    f3 c1;
    f3 c2;
}typedef f3x3;

struct f4x4
{
    f4 c0;
    f4 c1;
    f4 c2;
    f4 c3;
}typedef f4x4;

f2 f2_create(f32 a,f32 b);
f2 f2_create_f(f32 a);
f2 f2_add(f2 a,f2 b);
f2 f2_s_add(f32 a,f2 b);
f2 f2_sub(f2 a,f2 b);
f2 f2_s_sub(f32 a,f2 b); 
f2 f2_sub_s(f2 a,f32 b);
f2 f2_mul(f2 a,f2 b);
f2 f2_s_mul(f32 a,f2 b);
f2 f2_mul_s(f2 b,f32 a);
f2 f2_div(f2 a,f2 b);
f2 f2_s_div(f32 a,f2 b);
f2 f2_div_s(f2 a,f32 b);

f3 f3_create(f32 a,f32 b,f32 c);
f3 f3_create_f(f32 a);
f3 f3_add(f3 a,f3 b);
f3 f3_s_add(f32 a,f3 b);
f3 f3_sub(f3 a,f3 b);
f3 f3_s_sub(f32 a,f3 b);
f3 f3_sub_s(f3 a,f32 b);
f3 f3_mul(f3 a,f3 b);
f3 f3_mul_s(f3 b,f32 a);
f3 f3_s_mul(f32 a,f3 b);
f3 f3_div(f3 a,f3 b);
f3 f3_s_div(f32 a,f3 b);
f3 f3_div_s(f3 a,f32 b);
f3 f3_world_local_p(f4x4 m,f3 a);
f3 f3_local_world_p(f4x4 m,f3 a);

f4 f4_create(f32 a,f32 b,f32 c,f32 d);
f4 f4_create_f(f32 a);
f4 f4_add(f4 a,f4 b);
f4 f4_s_add(f32 a,f4 b);
f4 f4_sub(f4 a,f4 b);
f4 f4_s_sub(f32 a,f4 b);
f4 f4_sub_s(f4 a,f32 b);
f4 f4_mul(f4 a,f4 b);
f4 f4_s_mul(f32 a,f4 b);
f4 f4_div(f4 a,f4 b);
f4 f4_s_div(f32 a,f4 b);
f4 f4_div_s(f4 a,f32 b);

f3x3 f3x3_identity();
f3x3 f3x3_create_zero();
f3x3 f3x3_create_vector(f3 a,f3 b,f3 c);
f3x3 f3x3_create_row(f32 a,f32 b,f32 c);
f3x3 f3x3_create(f32 m00, f32 m01, f32 m02,
                 f32 m10, f32 m11, f32 m12, 
                 f32 m20, f32 m21, f32 m22);
f3x3 f3x3_create_from_quaternion(quaternion a);
f3x3 f3x3_transpose(f3x3 a);
f3x3 f3x3_look_rotation(f3 forward, f3 up);

f4x4 f4x4_identity();
f4x4 f4x4_create_zero();
f4x4 f4x4_create_row(f32 a,f32 b,f32 c,f32 d);
f4x4 f4x4_create_vector(f4 a,f4 b,f4 c,f4 d);
f4x4 f4x4_create(f32 m00, f32 m01, f32 m02, f32 m03,
                 f32 m10, f32 m11, f32 m12, f32 m13, 
                 f32 m20, f32 m21, f32 m22, f32 m23,
                 f32 m30, f32 m31, f32 m32, f32 m33);
f4x4 f4x4_create_from_f3x3rotation_translation(f3x3 rotation, f3 translation);
f4x4 f4x4_create_from_quaternion_translation(quaternion rotation,f3 translation);
f4x4 f4x4_create_with_scale(f32 x, f32 y, f32 z);
f4x4 f4x4_create_with_translate(f3 a);
f4x4 f4x4_create_from_trs(f3 t,quaternion r,f3 s);
f4x4 f4x4_inverse(f4x4 a);
    
f4x4 f4x4_transpose(f4x4 a);
f4x4 f4x4_mul(f4x4 a,f4x4 b);
f4 f4x4_mul_f4(f4x4 b,f4 a);
f4 f4_mul_f4x4(f4 a,f4x4 b);
    
quaternion quaternion_create(f32 x, f32 y, f32 z, f32 w);
quaternion quaternion_create_zero();
quaternion quaternion_create_f3x3(f3x3 a);
quaternion quaternion_create_f4x4(f4x4 a);
quaternion quaternion_create_f4(f4 a);
quaternion quaternion_look_rotation(f3 forward, f3 up);
quaternion quaternion_identity();
quaternion quaternion_mul(quaternion a,quaternion b);
f3 quaternion_mul_f3(quaternion q, f3 dir);
f3 quaternion_forward(quaternion q);
f3 quaternion_up(quaternion q);
f3 quaternion_right(quaternion q);

quaternion quaternion_normalize(quaternion a);
f32 quaternion_dot(quaternion a, quaternion b);
f32 quaternion_length(quaternion q);
f32 quaternion_length_sq(quaternion q);
quaternion quaternion_conjugate(quaternion q);
quaternion quaternion_nlerp(quaternion q1, quaternion q2, f32 t);
quaternion quaternion_inverse(quaternion q);
quaternion quaternion_slerp(quaternion q1, quaternion q2, f32 t);

f4x4 look_at(f3 eye,f3 target,f3 up);

f3 f3_rotate_by_f4x4(f4x4 a,f3 dir);
quaternion f3_axis_angle(f3 axis, f32 angle);
f3 f4x4_transform(f4x4 a, f3 b);

f32 safe_ratio_zero(f32 a,f32 b);

f3 cross(f3 a, f3 b);

f32 f2_sum(f2 v);
f32 f3_sum(f3 v);
f32 f4_sum(f4 v);

f32 f2_dot(f2 a, f2 b);
f32 f3_dot(f3 a, f3 b);
f32 f4_dot(f4 a, f4 b);

f32 f2_length(f2 v);
f32 f3_length(f3 v);
f32 f4_length(f4 v);

f2 f2_normalize(f2 v);
f3 f3_normalize(f3 v);
f4 f4_normalize(f4 v);

f32 clamp(f32 x,f32 a,f32 b);

f32 f2_length_sq(f2 v);
f32 f3_length_sq(f3 v);
f32 f4_length_sq(f4 v);

f32 lerp(f32 a,f32 b,f32 t);
f2 f2_lerp(f2 a, f2 b,f2 t);
f3 f3_lerp(f3 a, f3 b,f3 t);
f4 f4_lerp(f4 a, f4 b,f4 t);

f32 f2_distance(f2 a, f2 b);
f32 f3_distance(f3 a, f3 b);

f2 f2_sin(f2 x);
f3 f3_sin(f3 x);
f4 f4_sin(f4 x);

f2  f2_cos(f2 x);
f3  f3_cos(f3 x);
f4  f4_cos(f4 x);

void  f2_sincos(f2 x,f2* s,f2* c);
void  f3_sincos(f3 x,f3* s,f3* c);
void  f4_sincos(f4 x,f4* s,f4* c);

f32 sqroot(f32 a);;
f2  f2_sqroot(f2 a);
f3  f3_sqroot(f3 a);
f4  f4_sqroot(f4 a);

f32 rsqrt(f32 a);
f2  f2_rsqrt(f2 a);
f3  f3_rsqrt(f3 a);
f4  f4_rsqrt(f4 a);

f2  f2_abs(f2 x);
f3  f3_abs(f3 x);
f4  f4_abs(f4 x);

f32 unlerp(f32  a, f32  b, f32  x);
f2  f2_unlerp(f2 a, f2 b, f2 x);
f3  f3_unlerp(f3 a, f3 b, f3 x);
f4  f4_unlerp(f4 a, f4 b, f4 x);

f32 remap(f32  a, f32  b, f32  c, f32  d, f32  x);
f2  f2_remap(f2 a, f2 b, f2 c, f2 d, f2 x);
f3  f3_remap(f3 a, f3 b, f3 c, f3 d, f3 x);
f4  f4_remap(f4 a, f4 b, f4 c, f4 d, f4 x);

f32 mad(f32  a, f32  b, f32  c);
f2  f2_mad(f2 a, f2 b, f2 c);
f3  f3_mad(f3 a, f3 b, f3 c);
f4  f4_mad(f4 a, f4 b, f4 c);

f32 tangent(f32  x);
f2  f2_tangent(f2 x);
f3  f3_tangent(f3 x);
f4  f4_tangent(f4 x);

f2  f2_atan(f2 x);
f3  f3_atan(f3 x);
f4  f4_atan(f4 x);

f2  f2_atan2(f2 y, f2 x);
f3  f3_atan2(f3 y, f3 x);
f4  f4_atan2(f4 y, f4 x);

f2  f2_acos(f2 x);
f3  f3_acos(f3 x);
f4  f4_acos(f4 x);

f2  f2_floor(f2 x);
f3  f3_floor(f3 x);
f4  f4_floor(f4 x);

f2  f2_ceil(f2 x);
f3  f3_ceil(f3 x);
f4  f4_ceil(f4 x);

f2  f2_round(f2 x);
f3  f3_round(f3 x);
f4  f4_round(f4 x);

f2  f2_trunc(f2 x);
f3  f3_trunc(f3 x);
f4  f4_trunc(f4 x);

f2  f2_pow(f2 x, f2 y);
f3  f3_pow(f3 x, f3 y);
f4  f4_pow(f4 x, f4 y);

f2  f2_exp(f2 x);
f3  f3_exp(f3 x);
f4  f4_exp(f4 x);

f2  f2_exp2(f2 x);
f3  f3_exp2(f3 x);
f4  f4_exp2(f4 x);

f2  f2_fmod(f2 x, f2 y);
f3  f3_fmod(f3 x, f3 y);
f4  f4_fmod(f4 x, f4 y);

f2  f2_reflect(f2 i, f2 n);
f3  f3_reflect(f3 i, f3 n);
f4  f4_reflect(f4 i, f4 n);

f32 radians(f32 x);
f2  f2_radians(f2 x);
f3  f3_radians(f3 x);
f4  f4_radians(f4 x);

f32 degrees(f32 x);
f2  f2_degrees(f2 x);
f3  f3_degrees(f3 x);
f4  f4_degrees(f4 x);

f4 f4_negate(f4 x);

f4x4 init_pers_proj_matrix(f2 buffer_dim, f32 fov_y, f2 far_near);
//NOTE(Ray):When using this function remember that you have to take into account
//aspect ration for your size.
f4x4 init_ortho_proj_matrix(f2 size, f32 near_clip_plane, float far_clip_plane);
f4x4 init_screen_space_matrix(f2 buffer_dim);
f4x4 set_camera_view(f3 p,f3 forward_dir,f3 up_dir);
f3 f3_rotate(quaternion q, f3 dir);
//copy pasted from 
//https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624
f32 f32_random_range(f32 a, f32 b);
f3 f3_screen_to_world_point(f4x4 projection_matrix,f4x4 cam_matrix,f2 buffer_dim, f2 screen_xy,f32 z_depth);
f2 f2_world_to_screen_point(f4x4 projection_matrix,f4x4 camera_matrix,f2 buffer_dim, f3 p);
//END MATH API

//BEGIN 3D Tranform api

//NOTE(Ray):If these become a perf bottle neck look to seperate these out.
struct FMJ3DTrans
{
//world trans    
	f3 p;
	quaternion r;
	f3 s;
//local trans
	f3 local_p;    
	quaternion local_r;
	f3 local_s;
//matrix
	f4x4 m;
//local axis
	f3 forward;
	f3 up;
	f3 right;
}typedef FMJ3DTrans;

void fmj_3dtrans_matrix_set(FMJ3DTrans* ot);
f3 fmj_3dtrans_world_to_local_pos(FMJ3DTrans* ot,f3 a);
f3 fmj_3dtrans_local_to_world_pos(FMJ3DTrans* ot,f3 a);
void fmj_3dtrans_update(FMJ3DTrans* ot);
void fmj_3dtrans_init(FMJ3DTrans* ot);
f4x4 fmj_3dtrans_set_cam_view(FMJ3DTrans* ot);
f3 fmj_3dtrans_transform_dir(f4x4 a,f3 b);
f3 fmj_3dtrans_transform_p(f4x4 a,f3 b);

//END 3D Transform API

//Begin Sprite API
#define SIZE_OF_SPRITE_VERT_IN_BYTES ((sizeof(f32) * 3) + (4 * sizeof(f32)) + (2 * sizeof(f32)))//one p v3 + one color v4 + one uv v2 = one vert data
#define SIZE_OF_SPRITE_IN_BYTES (SIZE_OF_SPRITE_VERT_IN_BYTES * 6)

struct FMJSpriteBatch
{
    FMJMemoryArena arena;    
}typedef FMJSpriteBatch;

struct FMJSprite
{
    u64 id;
    u32 tex_id;
    f2 uvs[4];
    f4 color;
    bool is_visible;
    u64 material_id;
}typedef FMJSprite;

struct FMJSpriteNineSlice
{
    u32 tex_id;
    f2 uvs[4];
    f4 color;
    f4 slice_dim;
    bool is_visible;
}typedef FMJSpriteNineSlice;

void fmj_sprite_add_verts_(f32* v,f3 p[],f4 colors[],f2 uv[]);
void fmj_sprite_add_quad_(f32* v,f3 p,quaternion r,f2 dim,f4 color,f2 uv[]);
void fmj_sprite_add_rect(FMJMemoryArena* arena,f3 p[],f4 colors[],f2 uv[]);
void fmj_sprite_add_rect_with_dim(FMJMemoryArena* arena,f4 dim,f32 z,f4 color,f2 uv[]);
void fmj_sprite_add_quad(FMJMemoryArena* arena,f3 p,quaternion r,f3 scale,f4 colors,f2 uv[]);
FMJSprite fmj_sprite_init(u32 tex_id,f2 uvs[],f4 color,bool is_visible);
void fmj_sprite_add_quad_notrans(FMJMemoryArena* arena,f3 p,quaternion r,f3 scale,f4 colors,f2 uv[]);
//End Sprite API

//BEGIN UI API
struct FMJUIRect
{
    f4 dim;
    f4 anchor;
    f4 offset;
    f4 current_color;
    f4 color;
    f4 highlight_color;
    f32 z;
} typedef FMJUIRect;

enum FMJUINodeType
{
    fmj_ui_node_none,
    fmj_ui_node_label,
    fmj_ui_node_sprite,
    fmj_node_sprite_nine_slice
}typedef FMJUINodeType;

struct FMJUINode
{
    FMJUIRect rect;
    FMJStretchBuffer children;
    FMJString* text;
    bool interactable;
    bool use_anchor;
    
    FMJUINodeType type;
//TODO(Ray):Get rid of one of these two.    
    u32 st_id;
    FMJSprite sprite;
}typedef FMJUINode;

struct FMJUIHotNodeState
{
    f2 mouse_p;
    f2 prev_mouse_p;
    FMJUINode* node;
    FMJUINode* prev_node;
}typedef FMJUIHotNodeState;

struct FMJUIState
{
    FMJUINode parent_node;
    FMJUIHotNodeState hot_node_state;
}typedef FMJUIState;

f2 fmj_ui_get_rect_dim(FMJUIRect rect);
void fmj_ui_calculate_rect_dim(FMJUIRect* child_rect,FMJUIRect parent_rect);
void fmj_ui_get_rect_dim_from_p(FMJUIRect* child_rect,FMJUIRect parent_rect,f3 p,f2 dim);
void fmj_ui_evaluate_node(FMJUINode* node,FMJUIHotNodeState* hot_node_state);
void fmj_ui_evaluate_on_node_recursively(FMJUINode* node,void (*eval_func)(void*));
//END UI API

//BEGIN RENDER COMMAND API

struct FMJRenderGeometry
{
    f2 buffer_id_range;
    u64 count;
    u64 offset;
    u64 index_id;
    u64 index_count;
    bool is_indexed;
    f4 base_color;
}typedef FMJRenderGeometry;

struct FMJRenderMaterial
{
    u64 id;
    void* pipeline_state;//finalized depth stencil state etc... 
    f4 scissor_rect;
    f4 viewport_rect;
    u64 metallic_roughness_texture_id;
    f4 base_color;
}typedef FMJRenderMaterial;

struct FMJRenderCommand
{
    FMJRenderGeometry geometry;
    u64 material_id;
    u64 model_matrix_id;
    u64 camera_matrix_id;
    u64 perspective_matrix_id;
    
    //TODO(Ray):Create a mapping between pipeline state root sig slots..
    //and inputs from the application ie textures buffers etc..
    //for now we just throw on the simple ones we are using now. 
    u64 texture_id;
    bool is_indexed;
} typedef FMJRenderCommand;

//END RENDER COMMAND API


#define FMJ_TYPES_H
#endif
