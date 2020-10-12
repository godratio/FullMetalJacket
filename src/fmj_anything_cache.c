#include "fmj_types.h"
#define DEFAULT_ALIGNMENT 4

AnyCache fmj_anycache_init(u32 max_hash_states,umm size_of_thing,umm size_of_key,bool use_free_list)
{
    AnyCache result = {0};
    umm size_of_free_list_entry_index = sizeof(umm);
    result.key_size = size_of_key;
    result.hash = fmj_hashtable_init_(max_hash_states,size_of_key);
    result.anythings = fmj_stretch_buffer_init(10,size_of_thing,DEFAULT_ALIGNMENT);
    result.is_using_free_list = use_free_list;

    if(use_free_list)
        result.free_list = fmj_stretch_buffer_init(1,size_of_free_list_entry_index,DEFAULT_ALIGNMENT);
    result.is_init = true;
    return result;
}

AnyCache fmj_anycache_anysize_init(u32 max_hash_states,umm size_of_thing,bool use_free_list)
{
    AnyCache result = {0};
    umm size_of_free_list_entry_index = sizeof(umm);
    result.key_size = 0;
    result.hash = fmj_hashtable_init_(max_hash_states);
    result.anythings = fmj_stretch_buffer_init(10,size_of_thing,DEFAULT_ALIGNMENT);
    result.is_using_free_list = use_free_list;

    if(use_free_list)
        result.free_list = fmj_stretch_buffer_init(1,size_of_free_list_entry_index,DEFAULT_ALIGNMENT);
    result.is_init = true;
    return result;
}
    
bool fmj_anycache_exist(AnyCache* cache,void* key)
{
    return fmj_hashtable_contains(&cache->hash,key,cache->key_size);
}
    
bool fmj_anycache_anysize_exist(AnyCache* cache,void* key,u64 keysize)
{
    return fmj_hashtable_contains(&cache->hash,key,keysize);
}

bool fmj_anycache_anykeysize_add_to_free_list(AnyCache* cache,void* key,u64 keysize,void* thing)
{
    ASSERT(cache->is_using_free_list);
    u32 index = 0;
    if(fmj_anycache_exist(cache,key))
    {
        FMJHashAddElementResult r = {0};
        r.is_succeed = false;
        ASSERT(false);
        return r.is_succeed;            
    }

    if(cache->free_list.fixed.count > 0)
    {
        umm mi = fmj_stretch_buffer_get(umm,&cache->free_list,cache->free_list.fixed.count - 1);
        index = (u32)(mi);
        void* dst = fmj_stretch_buffer_checkout_ptr_(&cache->anythings,index);
        fmj_memory_copy(dst,thing,cache->anythings.fixed.unit_size);
        fmj_stretch_buffer_check_in(&cache->anythings);
        fmj_stretch_buffer_pop(&cache->free_list);
    }
    else
    {
        index = fmj_stretch_buffer_push(&cache->anythings,thing);            
    }
    
    u32* a = (u32*)index;
    FMJHashAddElementResult r = fmj_hashtable_add(&cache->hash,(void*)key,keysize,a);
    return r.is_succeed;    
}

bool fmj_anycache_add_to_free_list(AnyCache* cache,void* key,void* thing)
{
    ASSERT(cache->is_using_free_list);
    u32 index = 0;
    if(fmj_anycache_exist(cache,key))
    {
        FMJHashAddElementResult r = {0};
        r.is_succeed = false;
        ASSERT(false);
        return r.is_succeed;            
    }

    if(cache->free_list.fixed.count > 0)
    {
        umm mi = fmj_stretch_buffer_get(umm,&cache->free_list,cache->free_list.fixed.count - 1);
        index = (u32)(mi);
        void* dst = fmj_stretch_buffer_checkout_ptr_(&cache->anythings,index);
        fmj_memory_copy(dst,thing,cache->anythings.fixed.unit_size);
        fmj_stretch_buffer_check_in(&cache->anythings);
        fmj_stretch_buffer_pop(&cache->free_list);
    }
    else
    {
        index = fmj_stretch_buffer_push(&cache->anythings,thing);            
    }
    
    u32* a = (u32*)index;
    FMJHashAddElementResult r = fmj_hashtable_add(&cache->hash,(void*)key,cache->key_size,a);
    return r.is_succeed;
}

bool fmj_anycache_add(AnyCache* cache,void* key,void* thing)
{
    ASSERT(!cache->is_using_free_list);    
    u32 index = fmj_stretch_buffer_push(&cache->anythings,thing);
    u32* a = (u32*)index;
    FMJHashAddElementResult r = fmj_hashtable_add(&cache->hash,(void*)key,cache->key_size,a);
    return r.is_succeed;
}

bool fmj_anycache_anykeysize_add(AnyCache* cache,void* key,u64 keysize,void* thing)
{
    ASSERT(!cache->is_using_free_list);
    u32 index = fmj_stretch_buffer_push(&cache->anythings,thing);
    u32* a = (u32*)index;
    FMJHashAddElementResult r = fmj_hashtable_add(&cache->hash,(void*)key,keysize,a);
    return r.is_succeed;
}

void* fmj_anycache_get_(AnyCache* cache,void* key)
{
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,(void*)key,cache->key_size);
    umm index = (umm)ptr;
    void* result = fmj_stretch_buffer_get_(&cache->anythings, (u32)index);
    ASSERT(result);
    return result;
}

void* fmj_anycache_anykeysize_get_(AnyCache* cache,void* key,u64 keysize)
{
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,(void*)key,cache->key_size);
    umm index = (umm)ptr;
    void* result = fmj_stretch_buffer_get_(&cache->anythings, (u32)index);
    ASSERT(result);
    return result;
}

void* fmj_anycache_checkout_(AnyCache* cache,void* key)
{
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,(void*)key,cache->key_size);
    umm index = (umm)ptr;
    void* result = fmj_stretch_buffer_checkout_ptr_(&cache->anythings, (u32)index);
    ASSERT(result);
    return result;
}

void* fmj_anycache_anykeysize_checkout_(AnyCache* cache,void* key,u64 keysize)
{
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,(void*)key,cache->key_size);
    umm index = (umm)ptr;
    void* result = fmj_stretch_buffer_checkout_ptr_(&cache->anythings, (u32)index);
    ASSERT(result);
    return result;
}

void fmj_anycache_checkin_(AnyCache* cache)
{
    fmj_stretch_buffer_check_in(&cache->anythings);
}

void fmj_anycache_remove_free_list(AnyCache* cache,void* key)
{
    ASSERT(cache->is_using_free_list);
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,key,cache->key_size);
    umm index = (umm)ptr;
    fmj_stretch_buffer_push(&cache->free_list,(void*)&index);
    fmj_hashtable_remove(&cache->hash,key);
}

void fmj_anycache_anykeysize_remove_free_list(AnyCache* cache,void* key,u64 keysize)
{
    ASSERT(cache->is_using_free_list);
    u32* ptr = fmj_hashtable_get(u32,&cache->hash,key,cache->key_size);
    umm index = (umm)ptr;
    fmj_stretch_buffer_push(&cache->free_list,(void*)&index);
    fmj_hashtable_remove(&cache->hash,key);
}

void fmj_anycache_remove(AnyCache* cache,void* key)
{
    ASSERT(!cache->is_using_free_list);
    fmj_hashtable_remove(&cache->hash,key);
}

void* fmj_anycache_checkout_first_free_(AnyCache* cache)
{
    void* result = 0;
    if(cache->free_list.fixed.count > 0)
    {
        umm* mi = fmj_stretch_buffer_check_out(umm,&cache->free_list,cache->free_list.fixed.count - 1);
        ASSERT(mi);
        u32 index = (u32)(*mi);
        fmj_stretch_buffer_check_in(&cache->free_list);

        //checked out
        result = fmj_stretch_buffer_checkout_ptr_(&cache->anythings,index);
        fmj_stretch_buffer_pop(&cache->free_list);
    }
    return result;
}

void* fmj_anycache_checkout_first_free_with_predicate_(AnyCache* cache,bool (*predicate)(void*))
{
    void* result = 0;
    if(cache->free_list.fixed.count > 0)
    {
        umm* mi = fmj_stretch_buffer_check_out(umm,&cache->free_list,cache->free_list.fixed.count - 1);
        ASSERT(mi);
        u32 index = (u32)(*mi);
        fmj_stretch_buffer_check_in(&cache->free_list);
        
        result = fmj_stretch_buffer_checkout_ptr_(&cache->anythings,index);
        if(!predicate(result))
        {
            result = 0;
        }
        else
        {
            fmj_stretch_buffer_pop(&cache->free_list);
        }
    }
    return result;
}
    
void fmj_anycache_reset(AnyCache* cache)
{
    fmj_stretch_buffer_clear(&cache->anythings);
    fmj_stretch_buffer_clear(&cache->free_list);
    fmj_stretch_buffer_clear(&cache->hash.key_backing_array);
    fmj_fixed_buffer_clear(&cache->hash.keys);
    fmj_fixed_buffer_clear(&cache->hash.values);
    fmj_stretch_buffer_clear(&cache->hash.collisions);
    fmj_stretch_buffer_clear(&cache->hash.collision_free_list);
    cache->hash.collision_count = 0;
}

