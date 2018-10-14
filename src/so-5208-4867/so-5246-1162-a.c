/* SO 5246-1162 */
#include <stdio.h>
#include <wordexp.h>

static void expansion_demo(char const *str)
{
  printf("Before expansion: %s\n", str);

  wordexp_t exp;
  wordexp(str, &exp, 0);
  printf("After expansion: %s\n", exp.we_wordv[0]);
  wordfree(&exp);
}

int main(void)
{
  char const *str1 = "\\''\\\"\"\"\\\"TEST1\\\"\"\"\\\"'\\'";
  expansion_demo(str1);

  char const *str2 = "'\\'\"\\\"\\\"\"TEST2\"\\\"\\\"\"\\''";
  expansion_demo(str2);

  return 0;
}
