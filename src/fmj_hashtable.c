#include "fmj_types.h"

FMJHashTable fmj_hashtable_init_(u64 start_count,u64 key_size)
{
	FMJHashTable result = {0};
    result.collision_free_list = fmj_stretch_buffer_init(1, sizeof(u64),8);
    result.key_backing_array = fmj_stretch_buffer_init(1,key_size,8);
    
    result.key_size = key_size;
    ASSERT(key_size == result.key_backing_array.fixed.unit_size);
	result.keys = fmj_fixed_buffer_init(start_count,sizeof(FMJHashKeyEntry),8);
	result.values = fmj_fixed_buffer_init(start_count,sizeof(FMJHashValueEntry),8);
    result.table_size = start_count;
    result.collisions = fmj_stretch_buffer_init(1,sizeof(FMJHashCollisionEntry),8);
	return result;
}

u64 fmj_hashtable_meow_hash_func(void* buffer,uint64_t size)
{
    meow_u128 hash = MeowHash(MeowDefaultSeed, size, buffer);
    return MeowU64From(hash,0);
}

u64 fmj_hashtable_hash_func(FMJHashTable* h_table,void* buffer,uint64_t size)
{
	u64 result = 0;
	result = fmj_hashtable_meow_hash_func(buffer,size);
    return result % h_table->table_size;
}

FMJHashAddElementResult fmj_hashtable_add(FMJHashTable* h_table,void* key,u64 key_size,void* element)
{
    FMJHashAddElementResult result = {0};
    result.is_succeed = true;
	u64 hash_index = fmj_hashtable_hash_func(h_table,key,key_size);
    FMJHashKeyEntry e = {0};
    e.collision_count = 0;
    e.indexed = true;
    e.tombstoned = false;
    e.value_index = hash_index;
    e.collision_head = 0;
    e.collision_head_index = -1;
    FMJHashValueEntry v = {0};
    v.value = element;

	FMJHashKeyEntry* lu = fmj_fixed_buffer_get_any(FMJHashKeyEntry, &h_table->keys, hash_index);
    ASSERT(lu);
    if(lu->indexed == false || lu->tombstoned == true)
	{
        if(lu->tombstoned)
        {
            e.collision_count = lu->collision_count;
            e.collision_head_index = lu->collision_head_index;
            e.collision_head = lu->collision_head;
        }
        
        FMJHashKeyEntry* ke = fmj_fixed_buffer_get_any(FMJHashKeyEntry,&h_table->keys, hash_index);
        ASSERT(ke);
        *ke = e;
        FMJHashValueEntry* ve = fmj_fixed_buffer_get_any(FMJHashValueEntry,&h_table->values, hash_index);
        ASSERT(ve);
        *ve = v;
        ASSERT(key_size == h_table->key_backing_array.fixed.unit_size);
        lu->backing_index = fmj_stretch_buffer_push(&h_table->key_backing_array,key);
        ASSERT(lu->backing_index < h_table->key_backing_array.fixed.count);
	}
	else
	{
        void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,lu->backing_index);
        if(!memcmp(key,backing_key,h_table->key_size))
        {
            //If the key exist we skip not adding.
            //Value already exist will not add
            result.is_succeed = false;
            result.result = 0;
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            return result;
        }
        else
        {
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            FMJHashCollisionEntry* head_entry = fmj_stretch_buffer_check_out(FMJHashCollisionEntry,&h_table->collisions,lu->collision_head_index);
            FMJHashCollisionEntry* at = head_entry;
            int last_at_index = -1;
            //bool has_head = false;
            //if(head_entry)has_head = true;
            while(at)
            {
                ASSERT(!at->key.tombstoned);
                FMJHashKeyEntry key_entry = at->key;
                void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,key_entry.backing_index);
                if(!memcmp(key,backing_key,h_table->key_size))
                {
                    //If the key exist we skip adding.
                    //Value already exist will not add
                    result.is_succeed = false;
                    result.result = 0;
                    fmj_stretch_buffer_check_in(&h_table->key_backing_array);
                    return result;
                }
                last_at_index = at->index;
                //TODO(ray):reorder this algo so we can get rid of this function call.
                //should be ok in single threaded use as we are not going to be resizing the buffer
                //before access here.
                at = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,at->next_index);
                fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            }

            ++h_table->collision_count;
        
            FMJHashCollisionEntry ce = {0};
            ce.key = e;
            ce.value = v;
            ce.next_index = -1;
            ASSERT(key_size == h_table->key_backing_array.fixed.unit_size);
            ce.key.backing_index = fmj_stretch_buffer_push(&h_table->key_backing_array,key);

            u64 new_coll_index = 0;
            if(h_table->collision_free_list.fixed.count == 0)
            {
                new_coll_index = fmj_stretch_buffer_push(&h_table->collisions,(void*)&ce);
                //Must be refetched due to the possible resizing of the collision pointers!!!
                head_entry = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,lu->collision_head_index);
                FMJHashCollisionEntry* new_coll_entry = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,new_coll_index);
                ASSERT(new_coll_index >= 0 && new_coll_index <= h_table->table_size);
                new_coll_entry->index = new_coll_index;
            }
            else
            {
                new_coll_index = fmj_stretch_buffer_get(u64,&h_table->collision_free_list,h_table->collision_free_list.fixed.count - 1);
                ce.index = new_coll_index;
                ASSERT(new_coll_index >= 0 && new_coll_index <= h_table->table_size);
                ASSERT(new_coll_index != last_at_index);
                FMJHashCollisionEntry* col_entry = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,new_coll_index);
                ASSERT(col_entry);
                ASSERT(col_entry->key.tombstoned);
                ASSERT(col_entry->index == new_coll_index);
                *col_entry = ce;
                //YoyoPopVectorElement(&h_table->collision_free_list);
                --h_table->collision_free_list.fixed.count;
            }
            
            if(head_entry)
            {
                if(head_entry && head_entry->next_index != new_coll_index)
                {
                //Has a head collision entry but no other valid entries so we make the head point to the new collision entry
                   if(last_at_index == -1)
                   {
                       ASSERT(head_entry->next_index == -1);
                       //NOTE(RAY):We dont care if we overwrite the original head in the case it was retrieved from the free list
                       //as it was tombstoned so now an overwite  makes sense.
                       //But not in the case that we didnt retrieve from the free list.
                       //ASSERT(head_entry->index != new_coll_index);
                       last_at_index = head_entry->index;
                   }
                   
                   FMJHashCollisionEntry* prev_at = fmj_stretch_buffer_check_out(FMJHashCollisionEntry,&h_table->collisions,last_at_index);
                   ASSERT(prev_at->next_index == -1);
                   ASSERT(prev_at->next_index != new_coll_index);
                   ASSERT(prev_at->index != new_coll_index);
                   prev_at->next_index = new_coll_index;
                   fmj_stretch_buffer_check_in(&h_table->collisions);
                }
            }
            else
            {
                lu->collision_head_index = new_coll_index;
            }
            ++lu->collision_count;            
        }
        fmj_stretch_buffer_check_in(&h_table->collisions);
	}
    result.result = hash_index;
    return result;
}

void* fmj_hashtable_get_(FMJHashTable* h_table,void* key,u64 size)
{
	void* result = 0;
	u64 hash_index = fmj_hashtable_hash_func(h_table,key,size);
	FMJHashKeyEntry* lu = fmj_fixed_buffer_get_any(FMJHashKeyEntry,&h_table->keys,hash_index);
	if(lu->collision_count == 0)
	{
        if(!lu->tombstoned)
        {
            FMJHashValueEntry* ve = fmj_fixed_buffer_get_any(FMJHashValueEntry,&h_table->values, hash_index);
            result = ve->value;
        }
	}
	else
	{
        FMJHashKeyEntry* backing_key = fmj_stretch_buffer_check_out(FMJHashKeyEntry,&h_table->key_backing_array,lu->backing_index);
        if(!memcmp(key,(void*)backing_key,h_table->key_size))
        {
            FMJHashValueEntry* ve = fmj_fixed_buffer_get_any(FMJHashValueEntry,&h_table->values, hash_index);
            result = ve->value;
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
        }
        else
        {
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            
            FMJHashCollisionEntry* head_entry = fmj_stretch_buffer_check_out(FMJHashCollisionEntry,&h_table->collisions,lu->collision_head_index);
            FMJHashCollisionEntry* at = head_entry;
            while(at)
            {
                FMJHashKeyEntry key_entry = at->key;
                void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,key_entry.backing_index);
                if(!memcmp(key,backing_key,h_table->key_size))
                {
                    if(!key_entry.tombstoned)
                        result = at->value.value;
                }
                fmj_stretch_buffer_check_in(&h_table->key_backing_array);
                at = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,at->next_index);
            }
            fmj_stretch_buffer_check_in(&h_table->collisions);
        }
	}
	return result;
}

void fmj_hashtable_remove(FMJHashTable* h_table,void* key)
{
//Get the hash of from the table
    u64 hash_index = fmj_hashtable_hash_func(h_table,key,h_table->key_size);
	FMJHashKeyEntry* lu = fmj_fixed_buffer_get_any(FMJHashKeyEntry,&h_table->keys,hash_index);

    //Check if the collision is something is indexed or has a collision already
    //If we dont have a colision and its indexed we get the value entry and clear it out
    //let the hash key entry to tombstoned so that we know it has been removed already.
    //Remove the key backing entry.
    if(lu->collision_count == 0 && lu->indexed)
    {
        lu->tombstoned = true;
        FMJHashValueEntry* ve = fmj_fixed_buffer_get_any(FMJHashValueEntry,&h_table->values, hash_index);
        ve->value = 0;
        fmj_stretch_buffer_clear_item(&h_table->key_backing_array,lu->backing_index);
    }
    
    //We have a collision so we much check the element and potentionally all the collisions for an value
    //entry
    else
    {
        //First get the backing index
        u64 prev_index = 0;
        void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,lu->backing_index);
        //If we have a match with the backing key and the key that was passed in we know we have found the value
        // 0 out.
        if(!memcmp(key,backing_key,h_table->key_size))
        {
            FMJHashValueEntry* ve = fmj_fixed_buffer_get_any(FMJHashValueEntry,&h_table->values, hash_index);
            ve->value = 0;
            fmj_stretch_buffer_clear_item(&h_table->key_backing_array,lu->backing_index);
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
        }
        else
        {
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            //If we didnt have the main key entry now we check the collisions for thie entry.
            //We start at the collision head index store in the first key entry
            FMJHashCollisionEntry* head_entry = fmj_stretch_buffer_check_out(FMJHashCollisionEntry,&h_table->collisions,lu->collision_head_index);
            FMJHashCollisionEntry* at = head_entry;
            FMJHashCollisionEntry* prev_at = 0;
            bool found_match = false;
            uint64_t removed_index = 0;
            //Go through all the collision entries and check for a match against the key passed in.
            while(at)
            {
                FMJHashKeyEntry key_entry = at->key;
                void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,key_entry.backing_index);
                //If we ever get a match from the key entry backing index backing key and the key passed in we have found our value to 0 out and tombstone it.
                if(!key_entry.tombstoned && !memcmp(key,(void*)backing_key,h_table->key_size))
                {
                    removed_index = at->index;
                    at->key.tombstoned = true;
                    at->value.value = 0;
                    fmj_stretch_buffer_clear_item(&h_table->key_backing_array,key_entry.backing_index);
                    found_match = true;
                    fmj_stretch_buffer_check_in(&h_table->key_backing_array);                    
                    break;
                }
                //after we check for a match we set up the next iteration
                //we keep one prev_at and
                prev_at = at;
                at = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,at->next_index);
                fmj_stretch_buffer_check_in(&h_table->key_backing_array);                    
            }

            //Must patch up the head.  And the prev next indices.
            if(found_match)
            {
                uint64_t free_index = removed_index;
                //If we are the head remove the head if there is a next index set that to be the new
                if(free_index == lu->collision_head_index)
                {
                    ASSERT(at->index == lu->collision_head_index);
                    if(head_entry->next_index > -1)
                    {
                        ASSERT(at->index == lu->collision_head_index);
                        lu->collision_head_index = head_entry->next_index;
                    }
                    else
                    {
                        lu->collision_head_index = -1;
                    }
                    //Making sure to no longer point this at any other collisions on a chain
                    head_entry->next_index = -1;
                }

                //patching up the link if there was any between the one we removed
                if(prev_at)
                {
                    ASSERT(prev_at->next_index >= 0 && prev_at->next_index <= h_table->table_size);
                    ASSERT(prev_at->next_index == at->index);
                    if(at->next_index > -1)
                    {
                        prev_at->next_index = at->next_index;
                    }
                    else
                    {
                        prev_at->next_index = -1;                        
                    }
                    //Making sure to no longer point this at any other collisions on a chain
                    at->next_index = -1;
                }
                ASSERT(free_index >= 0 && free_index <= h_table->table_size);
                fmj_stretch_buffer_push(&h_table->collision_free_list,(void*)&free_index);
                fmj_stretch_buffer_check_in(&h_table->collisions);
            }
            else
            {
            //printf("YOYOHASHTABLE::Could not find match to remove item.!");
            }
        }
    }
}

bool fmj_hashtable_contains(FMJHashTable* h_table,void* key,uint64_t size)
{
    uint64_t hash_index = fmj_hashtable_hash_func(h_table,key,size);
    FMJHashKeyEntry* lu = fmj_fixed_buffer_get_any(FMJHashKeyEntry,&h_table->keys,hash_index);
    if(lu->indexed && lu->collision_count == 0)
    {
        if(lu->tombstoned)
        {
            return false;            
        }
        else
        {
            void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,lu->backing_index);
            //ASSERT(backing_key);
            if(!memcmp(key,(void*)backing_key,h_table->key_size))
            {
                fmj_stretch_buffer_check_in(&h_table->key_backing_array);
                return true;
            }
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
        }
    }
    else if(lu->indexed)//collision
    {
        void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,lu->backing_index);
        ASSERT(backing_key);
        if(!memcmp(key,(void*)backing_key,h_table->key_size))
        {
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            return true;
        }
        else
        {
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
            
            FMJHashCollisionEntry* head_entry = fmj_stretch_buffer_check_out(FMJHashCollisionEntry,&h_table->collisions,lu->collision_head_index);
            FMJHashCollisionEntry* at = head_entry;
            while(at)
            {
                FMJHashKeyEntry key_entry = at->key;
                void* backing_key = fmj_stretch_buffer_check_out(void*,&h_table->key_backing_array,key_entry.backing_index);
                if(!memcmp(key,(void*)backing_key,h_table->key_size))
                {
                    fmj_stretch_buffer_check_in(&h_table->key_backing_array);                    
                    if(key_entry.tombstoned)
                        return false;
                    else
                        return true;
                }
                at = (FMJHashCollisionEntry*)fmj_stretch_buffer_get_(&h_table->collisions,at->next_index);
                fmj_stretch_buffer_check_in(&h_table->key_backing_array);                    
            }
            fmj_stretch_buffer_check_in(&h_table->key_backing_array);
        }
        
    }
    return false;
}



