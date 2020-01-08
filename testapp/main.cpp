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
    char buf[1000];    
    fgets(buf,1000,stdin);
    return 0;
}

