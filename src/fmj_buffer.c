
#include "fmj_types.h"

    //TODO(ray): Allow the option to pass in your own allocator or a pointer to your own memory
FMJFixedBuffer fmj_fixed_buffer_init(umm capacity,umm unit_size,u32 alignment)
{
    ASSERT(unit_size >= alignment);    
    ASSERT(unit_size > 0);
    FMJFixedBuffer result = {0};
	umm start_alloc_size = capacity * unit_size + (alignment*capacity);
    result.total_size = 0;
    result.unit_size = unit_size;
    result.capacity = capacity;
    result.alignment = alignment;
    
    result.at_index = 0;
    result.start_at = -1;

    void* base = fmj_os_allocate(start_alloc_size);
    result.mem_arena = fmj_arena_init(start_alloc_size,base);
    result.count = 0;
    
    result.base = result.mem_arena.base;
    
    FMJMemoryArena temp = {0};
    temp.used = unit_size;
    temp.base = result.mem_arena.base;
    temp.size = start_alloc_size;
    umm offset = fmj_arena_get_alignment_offset(&temp,alignment);
    result.unit_size = unit_size + offset;

    return result;
}

void fmj_fixed_buffer_clear(FMJFixedBuffer *buffer)
{
	ASSERT(buffer);
    buffer->mem_arena.used = 0;
    buffer->total_size = 0;
	buffer->count = 0;
	buffer->at_index = 0;
	buffer->start_at = -1;
}

void fmj_fixed_buffer_free(FMJFixedBuffer *buffer)
{
	if (buffer->total_size > 0)
	{
		fmj_fixed_buffer_free(buffer);
		buffer->total_size = 0;
        buffer->count = 0;
        fmj_os_deallocate(buffer->mem_arena.base, buffer->mem_arena.size);
		buffer->base = 0;
	}
}

u64 fmj_fixed_buffer_push(FMJFixedBuffer* buffer, void* element)
{
    ASSERT(buffer && element);
	ASSERT(buffer->start_at == -1);//You must have forget to reset the buffer or are trying to resize during iteration.
    FMJMemoryArenaPushParams mem_params = fmj_arena_push_params_default();
    mem_params.flags = fmj_arena_push_params_flag_none;
    mem_params.alignment = buffer->alignment;
    uint8_t *ptr = (uint8_t*)PUSHSIZE(&buffer->mem_arena, (umm)buffer->unit_size,mem_params);
    void* dst = memcpy(ptr,element,buffer->unit_size);
    ASSERT(dst == ptr);
    buffer->total_size = buffer->mem_arena.used;
    return buffer->count++;
}

void* fmj_fixed_buffer_get_(FMJFixedBuffer* buffer, u64 index)
{
	ASSERT(buffer);
	if (index < 0 || index > buffer->count - 1 || buffer->count == 0)return 0;
	return  (uint8_t*)buffer->base + (index * buffer->unit_size);
}

void* fmj_fixed_buffer_get_any_(FMJFixedBuffer* buffer, u64 index)
{
	ASSERT(buffer);
	ASSERT(buffer->start_at == -1);//You must have forget to reset the buffer or are trying to resize during iteration.    
//	if (index < 0 || index > buffer->count - 1 || buffer->capacity == 0)return 0;
    buffer->total_size += buffer->unit_size;
    buffer->count++;
	return  (uint8_t*)buffer->base + (index * buffer->unit_size);
}

void fmj_fixed_buffer_pop(FMJFixedBuffer* buffer)
{
    ASSERT(buffer);
    if(buffer->count == 0)return;
    ASSERT(buffer->mem_arena.size > 0);
    ASSERT((buffer->mem_arena.used - buffer->unit_size) >= 0) ;
    buffer->mem_arena.used -= buffer->unit_size;
	buffer->total_size -= buffer->unit_size;
	buffer->count--;
}

FMJStretchBuffer fmj_stretch_buffer_init(umm capacity,umm unit_size,u32 alignment)
{
    ASSERT(unit_size >= alignment);
    ASSERT(unit_size > 0);
    FMJStretchBuffer result = {0};
	umm start_alloc_size = capacity * unit_size;
    result.fixed.total_size = 0;
    result.fixed.unit_size = unit_size;
    result.fixed.capacity = capacity;
    result.fixed.at_index = 0;
    result.fixed.start_at = -1;
    result.borrow_count = 0;
    //TODO(ray): Allow the option to pass in your own allocator or a pointer to your own memory
    void* base = fmj_os_allocate(start_alloc_size);
    result.fixed.mem_arena = fmj_arena_init(start_alloc_size,base);
    result.fixed.count = 0;

    result.fixed.base = result.fixed.mem_arena.base;
    
    //umm alignment = 8;
    FMJMemoryArena temp = {0};
    temp.used = unit_size;
    temp.base = result.fixed.mem_arena.base;
    temp.size = start_alloc_size;
    umm offset = fmj_arena_get_alignment_offset(&temp,alignment);
    result.fixed.unit_size = unit_size + offset;
    return result;
}

u64 fmj_stretch_buffer_push(FMJStretchBuffer* buffer, void* element)
{
    ASSERT(buffer && element);
    //An assert here means you must have forget to reset the buffer or are trying to resize during 
	ASSERT(buffer->fixed.start_at == -1);
    if(buffer->fixed.mem_arena.size <= (buffer->fixed.unit_size) * (buffer->fixed.count + 1))
    {
        //An Assert here means you have resized while pointers are still being borrowed
        //OR You have not been return the pointers back after your done with them
        ASSERT(buffer->borrow_count == 0);
        
        umm old_size = buffer->fixed.mem_arena.size;
        float new_count = fmax(round((float)(buffer->fixed.count * buffer->resize_ratio)),1);
		umm new_size = buffer->fixed.mem_arena.size + ((buffer->fixed.unit_size) * new_count);
        uint8_t* old_base_ptr = (uint8_t*)buffer->fixed.mem_arena.base;
		buffer->fixed.base = fmj_os_allocate(new_size);
        buffer->fixed.mem_arena.base = buffer->fixed.base;
        buffer->fixed.mem_arena.size = new_size;
        
		memcpy(buffer->fixed.base, (void*)old_base_ptr, buffer->fixed.total_size);
        
		fmj_os_deallocate(old_base_ptr, old_size);
        
        umm alignment = 8;
        FMJMemoryArena temp = {0};
        temp.used = buffer->fixed.mem_arena.used;
        temp.base = buffer->fixed.mem_arena.base;
        temp.size = buffer->fixed.mem_arena.size;
        umm offset = fmj_arena_get_alignment_offset(&temp,alignment);
        //All 64 bit systems should be giving us addresses at 8 byte boundaries.
        //Furthermore the compilers all should be inserting padding to any structs so that we only are accessing memory on 8 byte
        //boundaries if for any reason this does not hold true we need to know right away.
        ASSERT(offset == 0);
    }
    return fmj_fixed_buffer_push(&buffer->fixed,element);
}

void* fmj_stretch_buffer_checkout_ptr_(FMJStretchBuffer* buffer,u64 index)
{
	ASSERT(buffer);
	if (index < 0 || index > buffer->fixed.count - 1 || buffer->fixed.count == 0)
    { 
        return 0;   
    }
    else
    {
        buffer->borrow_count++;
        return  (uint8_t*)buffer->fixed.base + (index * buffer->fixed.unit_size);               
    }
}

void* fmj_stretch_buffer_get_(FMJStretchBuffer* buffer,u64 index)
{
	ASSERT(buffer);
    return fmj_fixed_buffer_get_(&buffer->fixed,index);
}

void* fmj_stretch_buffer_get_any_(FMJStretchBuffer* buffer,u64 index)
{
	ASSERT(buffer);
    return fmj_fixed_buffer_get_any_(&buffer->fixed,index);
}

void fmj_stretch_buffer_check_in(FMJStretchBuffer* buffer)
{
    if(buffer->borrow_count > 0)
        buffer->borrow_count--;
}

void fmj_fixed_buffer_clear_item(FMJFixedBuffer* b,u64 i)
{
	ASSERT(b);
	void* location = (uint8_t*)b->base + (i * b->unit_size);
	uint8_t* ptr = (uint8_t*)location;
	{
		umm byte_count = b->unit_size;
		umm index = 0;
		while (index < byte_count)
		{
			*ptr++ = 0;
			index++;
		}
	}
}

void fmj_stretch_buffer_pop(FMJStretchBuffer* b)
{
    ASSERT(b);
    fmj_fixed_buffer_pop(&b->fixed);    
}

void fmj_stretch_buffer_clear_item(FMJStretchBuffer* s,u64 i)
{
    fmj_fixed_buffer_clear_item(&s->fixed,i);
}

void fmj_stretch_buffer_clear(FMJStretchBuffer *b)
{
	ASSERT(b);
    fmj_fixed_buffer_clear(&b->fixed);
    b->borrow_count = 0;
}

void fmj_stretch_buffer_free(FMJStretchBuffer *b)
{
    ASSERT(b);
    fmj_fixed_buffer_free(&b->fixed);
    b->borrow_count = 0;    
}

