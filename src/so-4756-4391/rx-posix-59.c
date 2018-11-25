/* SO 4756-4391 */
#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(void)
{
    char *source = "change@/devices/soc/799999.i2c/i2c-3/3-0015/power_supply/battery";
    // char * regexString = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";
    size_t maxGroups = 5;
    char *regexString =  "([a-zA-Z]+)@\\/(.*)\\/([a-zA-z]+)\\/([a-zA-z]+)";

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    int rc;
    if ((rc = regcomp(&regexCompiled, regexString, REG_EXTENDED)) != 0)
    {
        char buffer[1024];
        regerror(rc, &regexCompiled, buffer, sizeof(buffer));
        printf("Could not compile regular expression (%d: %s).\n", rc, buffer);
        return 1;
    }
    if ((rc = regexec(&regexCompiled, source, maxGroups, groupArray, 0)) != 0)
    {
        char buffer[1024];
        regerror(rc, &regexCompiled, buffer, sizeof(buffer));
        printf("Could not execute regular expression (%d: %s).\n", rc, buffer);
        return 1;
    }

    printf("Match successful:\n");
    for (size_t i = 0; i < maxGroups; i++)
    {
        int so = groupArray[i].rm_so;
        int eo = groupArray[i].rm_eo;
        printf("%zu: %d..%d [%.*s]\n", i, so, eo, eo - so, &source[so]);
    }

    regfree(&regexCompiled);

    return 0;
}
