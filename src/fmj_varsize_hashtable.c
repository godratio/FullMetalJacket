#include "fmj_types.h"


FMJHash fmj_hash_create()
{
    FMJHash result = {};
    result.key_backing_array = fmj_stretch_buffer_init(1,sizeof(u64),8);
    result.keys = fmj_stretch_buffer_init(1,sizeof(FMJHashKey),8);
    result.values = fmj_stretch_buffer_init(1,sizeof(FMJHashValue),8);
    result.collisions = fmj_stretch_buffer_init(1,sizeof(FMJHashCollision),8);
    //If this changes we have to recalculate all the keys.
    result.table_size = start_count;
    return result;
}

FMJHashAddElementResult fmj_hash_add(FMJHash* hashtable,void* key,u64 keysize,void* element,u64 elementsize)
{
    FMJHashAddElementResult result = {0};

    u64 hash_index = fmj_hashtable_hash_func(hashtable,key,key_size);

    FMJHashKeyEntry e = {0};
    e.collision_count = 0;
    e.value_index = hash_index;
    e.collision_head = 0;
    e.collision_head_index = -1;
    FMJHashValueEntry v = {0};
    v.value = element;
    
}


