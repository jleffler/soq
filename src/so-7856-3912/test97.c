/* SO 7856-3912 */

//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
//#include "acutest.h"
//#include "FileBuf.h"

/* Check configuration */
#ifndef INCLUDE_FILE_NAME
#error You must define INCLUDE_FILE_NAME as the name of the source file to test
#endif /* INCLUDE_FILE_NAME */
#ifndef FUNCTION_UNDER_TEST
#error You must define FUNCTION_UNDER_TEST as the name of the function under test
#endif /* FUNCTION_UNDER_TEST */

#include INCLUDE_FILE_NAME

#define TEST_FUNCTION_NAME(name)    test_ ## name ## _success
#define TEST_FUNCTION(name)         TEST_FUNCTION_NAME(name)

#define TEST_ARRAY_ENTRY(name)      #name, name
#define TEST_ARRAY_EXPANSION(name)  TEST_ARRAY_ENTRY(name)
#define TEST_ARRAY_MAPPING(name)    TEST_ARRAY_EXPANSION(TEST_FUNCTION(name))


void TEST_FUNCTION(FUNCTION_UNDER_TEST)(void)
{
    /* The lines and line lengths are at most 1024 in sample1.txt. */
    char buf[1024];
    char *lines[1024];
    size_t line_count = 0;
    FILE *const fp = fopen("test/sample.txt", "r");

    TEST_ASSERT(fp);

    while (fgets(buf, sizeof buf, fp)) {
        buf[strcspn(buf, "\n")] = '\0';
        TEST_ASSERT((lines[line_count] = strdup(buf)));
        ++line_count;
    }
    
    rewind(fp);

    FileBuf fbuf = {};

    TEST_CHECK(FUNCTION_UNDER_TEST(fp, &fbuf));
    TEST_CHECK(fbuf.count == 555);
    TEST_CHECK(fbuf.size == 120635);

    for (size_t i = 0; i < fbuf.count; ++i) {
        TEST_CHECK((strcmp(lines[i], fbuf.lines[i].line) == 0));
    }

    fclose(fp);
}

TEST_ARRAY_TYPE Test_Array_Name[] = {
    { TEST_ARRAY_MAPPING(FUNCTION_UNDER_TEST) },
    { nullptr, nullptr },
};
