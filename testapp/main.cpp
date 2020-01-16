extern "C"
{
#include "../src/fmj.h"
}

#include <stdio.h>

void* test_run_thread(void* data)
{
    printf("test thread spawned from thread %d. \n",*(u32*)data);
    s64 value =  *(s64*)data;

    s64 new_value = 1010;
    s64 comperand = *(s64*)data;

    u64 old_value = fmj_thread_atomic_compare_exchange64((s64*)&value,new_value,comperand);
    if(value == new_value)
    {
        printf("compare exchange has occured.\n");
    }
    else
    {
        printf("compare exchange has NOT occured\n");
    }

    s64 p_new_value = new_value;
    u64 add_old_value = fmj_thread_atomic_increment64(&new_value);
    printf("atomice add increment by 1 old_value %d : new_value %d. \n",(u32)p_new_value,(u32)new_value);

    p_new_value = new_value;
    add_old_value = fmj_thread_atomic_decrement64(&new_value);
    printf("atomice subtract decrement by 1 old_value %d : new_value %d. \n",(u32)p_new_value,(u32)new_value);

    p_new_value = new_value;
    add_old_value = fmj_thread_atomic_add64(&new_value,1000);
    printf("atomice add by 1000 old_value %d : new_value %d. \n",(u32)p_new_value,(u32)new_value);

    FMJTicketMutex tm = {0};
    printf("tm sticket %d : serving before %d. \n",(u32)tm.ticket,(u32)tm.serving);    
    fmj_thread_begin_ticket_mutex(&tm);
    printf("tm sticket %d : serving during %d. \n",(u32)tm.ticket,(u32)tm.serving);
    fmj_thread_end_ticket_mutex(&tm);
    printf("tm sticket %d : serving after %d. \n",(u32)tm.ticket,(u32)tm.serving);    
    return 0;
}

int main()
{

    FMJMemoryArena test_string_arena = fmj_arena_allocate(FMJMEGABYTES(2));
    FMJString test_string = fmj_string_create("test",&test_string_arena);
    
    char* cc = "testchar";
//strings
    int test_length = fmj_string_char_length(cc);
    printf("char length is %d.\n",test_length);
    test_length = fmj_string_length(&test_string);
    printf("string length is %d.\n",test_length);
//safe versions
    test_length = fmj_string_char_length_safe(cc,100);
    printf("char length safe is %d.\n",test_length);
    test_length = fmj_string_length_safe(&test_string,100);
    printf("string length safe is %d.\n",test_length);

    FMJString test_string_2 = fmj_string_create_from_ptr(test_string.string,test_string.string + test_string.length,&test_string_arena);
    test_length = fmj_string_length_safe(&test_string_2,test_string.length);    
    printf("string is %s length is %d.\n",test_string_2.string,test_length);

    FMJString test_string_3 = fmj_string_create_from_length(test_string.string,test_string.length,&test_string_arena);
    test_length = fmj_string_length_safe(&test_string_2,test_string.length);    
    printf("string is %s length is %d.\n",test_string_2.string,test_length);

    bool comp_result = fmj_string_cmp(test_string,test_string_2);
    printf("string a %s string b %s comparision is %d. \n",test_string.string,test_string_2.string,(int)comp_result);

    comp_result = fmj_string_cmp_char(test_string,cc);
    printf("string a %s string b %s comparision is %d. \n",test_string.string,cc,(int)comp_result);

    char* fake_path = "fakepath/with/fake/filename.png";
    FMJString file_name = fmj_string_get_filename(fake_path,fmj_string_char_length_safe(fake_path,100),&test_string_arena);
    printf("extracted filename is %s. \n",file_name.string);

    FMJString file_name_ext = fmj_string_get_extension(file_name,&test_string_arena,false);
    printf("extracted filename extension is %s. \n",file_name_ext.string);

    FMJString file_name_stripped_ext = fmj_string_strip_extension(file_name,&test_string_arena);
    printf("stripped filename extension is %s. \n",file_name_stripped_ext.string);

    FMJString padded_string = fmj_string_pad_right(file_name_stripped_ext,'-',10,&test_string_arena);
    printf("padded string is %s. \n",padded_string.string);

    FMJString appended_string = fmj_string_append(padded_string,file_name_ext,&test_string_arena);
    printf("front %s , back %s appended string is %s. \n",padded_string.string,file_name_ext.string,appended_string.string);

    FMJFixedBuffer fbtest = fmj_fixed_buffer_init(1000,sizeof(u64),8);
    u64 element = 1000;
    u64 index = fmj_fixed_buffer_push(&fbtest,(void*)&element);
    u64 fb_result = fmj_fixed_buffer_get(u64,&fbtest,index);     
    printf("Fixed Buffer test result %llu. \n",fb_result);

    FMJStretchBuffer sb_test = fmj_stretch_buffer_init(1,sizeof(u64),8);
    fb_result += 1000;
    index = fmj_stretch_buffer_push(&sb_test,(void*)&fb_result);
    fb_result = fmj_stretch_buffer_get(u64,&sb_test,index);
    printf("Stretchy Buffer test result %llu. \n",fb_result);    

//TEST HASHTABLE
    FMJHashTable test_ht = fmj_hashtable_init(4096,u64);
    u64 test_data = 777;
    u64 test_key = 1000;
    fmj_hashtable_add(&test_ht,&test_key,sizeof(u64),&test_data);

    u64 data = *fmj_hashtable_get(u64,&test_ht,&test_key,sizeof(u64));
    printf("hash test result %llu. \n",data);

    if(fmj_hashtable_contains(&test_ht,&test_key,sizeof(u64)))
    {
        printf("hash test result exists true : true. \n");        
    }
    
    fmj_hashtable_remove(&test_ht,&test_key);

    if(fmj_hashtable_contains(&test_ht,&test_key,sizeof(u64)))
    {
        printf("hash test result exists true should be false. \n");
        ASSERT(false);
    }
    else
    {
        printf("hash test result exists false. \n");        
    }

    u64* datap = fmj_hashtable_get(u64,&test_ht,&test_key,sizeof(u64));
    printf("hash test result %llu. \n",(u64)datap);


    fmj_hashtable_add(&test_ht,&test_key,sizeof(u64),&test_data);

    data = *fmj_hashtable_get(u64,&test_ht,&test_key,sizeof(u64));
    printf("hash test result %llu. \n",data);    

//TEST ANYTHING CACHE
    AnyCache test_ac = fmj_anycache_init(4096,sizeof(u64),sizeof(u64),false);
    u64 test_ac_key = 2000;
    u64 test_ac_value = 7771;

    if(fmj_anycache_exist(&test_ac,(void*)&test_ac_key))
    {
        ASSERT(false);
    }
    else
    {
        printf("TEST AC: Should be false. \n");            
    }

    fmj_anycache_add(&test_ac,(void*)&test_ac_key,(void*)&test_ac_value);

    if(fmj_anycache_exist(&test_ac,(void*)&test_ac_key))
    {
        printf("TEST AC: Should be True. \n");            
    }
    else
    {
        ASSERT(false);        
    }

    u64 ac_value = fmj_anycache_get(u64,&test_ac,(void*)&test_ac_key);
    printf("TESTAC result value:  %llu. \n",ac_value);        

    fmj_anycache_remove(&test_ac,&test_ac_key);
    if(fmj_anycache_exist(&test_ac,(void*)&test_ac_key))
    {
        ASSERT(false);
    }
    else
    {
        printf("TEST AC: Should be false because removed. \n");            
    }

//Anything cache with free list tests.
    AnyCache test_ac_fl = fmj_anycache_init(4096,sizeof(u64),sizeof(u64),true);    

    u64* fill_ptr = fmj_anycache_checkout_first_free(u64,&test_ac_fl);

    if(fill_ptr)
    {
        ASSERT(false);
    }
    else
    {
        printf("TEST ACFL: NO Free items yet. \n");                    
    }

    if(fmj_anycache_exist(&test_ac_fl,(void*)&test_ac_key))
    {
        ASSERT(false);
    }
    else
    {
        printf("TEST AC: Should be false. \n");            
    }

    fmj_anycache_add_to_free_list(&test_ac_fl,(void*)&test_ac_key,(void*)&test_ac_value);

    if(fmj_anycache_exist(&test_ac_fl,(void*)&test_ac_key))
    {
        printf("TEST AC: Should be True. \n");            
    }
    else
    {
        ASSERT(false);        
    }

    u64 ac_value_fl = fmj_anycache_get(u64,&test_ac_fl,(void*)&test_ac_key);
    printf("TESTAC result value:  %llu. \n",ac_value);        

    fmj_anycache_remove_free_list(&test_ac_fl,&test_ac_key);
    if(fmj_anycache_exist(&test_ac_fl,(void*)&test_ac_key))
    {
        ASSERT(false);
    }
    else
    {
        printf("TEST AC: Should be false because removed. \n");            
    }

    fill_ptr = fmj_anycache_checkout_first_free(u64,&test_ac_fl);
    if(fill_ptr)
    {
        printf("TEST ACFL: Now we have a free item. \n");                    
    }
    else
    {
        ASSERT(false);
    }

    char* path = "./";
    FMJFileDirInfoResult file_infos = fmj_file_platform_get_all_files_in_dir(path,&test_string_arena);

    for(int i = 0;i < file_infos.files.count;++i)
    {
        FMJFileInfo* info = (FMJFileInfo*)file_infos.files.base + i;
        printf("file name : %s \n",info->name.string);

        FMJFileReadResult rr = fmj_file_platform_read_entire_file(info->name.string);
        printf("file name : %d \n",(u32)rr.content_size);        
    }

    u64 cpu_core_count = fmj_thread_get_cpu_core_count();
    printf("cpu core count : %d \n",(u32)cpu_core_count);
    
    u64 thread_id =  fmj_thread_get_thread_id();
    printf("threadid : %d \n",(u32)thread_id);

    FMJThread thread = fmj_thread_create(test_run_thread,&thread_id);

    //Math testing
    f32_2 a = float2(0,0.333456f);
    printf("float2 values: x: %f  y: %f .\n",a.x,a.y);
    printf("float2 values: x: %f  y: %f .\n",a.xy[0],a.xy[1]);
    
    char buf[1000];    
    fgets(buf,1000,stdin);
    return 0;
}

