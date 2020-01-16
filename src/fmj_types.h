//NOTE(ray):We will not be pursuing this any further for now as its assumed any games
//that I would make will use the preexisting math lib in C++.
//I may however decide against that come back here and finisht this or use someone elses
//C mathlib

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

union f32_2
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
    
} typedef f32_2;
f32_2 float2(f32 a,f32 b);
f32_2 float2_add(f32_2 a, f32_2 b);
f32_2 float2_s_add(f32 a, f32_2 b);
f32_2 float2_sub(f32_2 a, f32_2 b);
f32_2 float2_s_sub(f32 a, f32_2 b); 
f32_2 float2_sub_s(f32_2 a, f32 b);
f32_2 float2_mul(f32_2 a, f32_2 b);
f32_2 float2_s_mul(f32 a,f32_2 b);
f32_2 float2_div(f32_2 a, f32_2 b);
f32_2 float2_s_div(float a, f32_2 b);
f32_2 float2_div_s(f32_2 a, float b);

//END MATH API
#define FMJ_TYPES_H
#endif
