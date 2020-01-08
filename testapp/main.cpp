extern "C"
{
#include "../src/fmj.h"
}

#include <stdio.h>

int main()
{
    FMJString test_string = {true,4,"abcd\0"};
    
    char* cc = "testchar";
//strings
    int test_length = fmj_char_length(cc);
    printf("char length is %d.\n",test_length);
    test_length = fmj_string_length(&test_string);
    printf("string length is %d.\n",test_length);
//safe versions
    test_length = fmj_char_length_safe(cc,100);
    printf("char length safe is %d.\n",test_length);
    test_length = fmj_string_length_safe(&test_string,100);
    printf("string length safe is %d.\n",test_length);

    fgets(cc,0,0);
    return 0;
}

