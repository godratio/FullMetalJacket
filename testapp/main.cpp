extern "C"
{
#include "../src/fmj.h"
}

#include <stdio.h>

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
    
    char buf[1000];    
    fgets(buf,1000,stdin);
    return 0;
}

