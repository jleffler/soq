/* SO 7856-3912 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "acutest.h"

#include "../src/FileBuf.h"
#include "../src/readlines_fread.c"

void test_readlines_fread_success(void)
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

    TEST_CHECK(readlines_fread(fp, &fbuf));
    TEST_CHECK(fbuf.count == 555);
    TEST_CHECK(fbuf.size == 120635);

    for (size_t i = 0; i < fbuf.count; ++i) {
        TEST_CHECK((strcmp(lines[i], fbuf.lines[i].line) == 0));
    }

    fclose(fp);
}

TEST_LIST = {
    { "test_readlines_fread_success", test_readlines_fread_success },
    { nullptr, nullptr },
};
