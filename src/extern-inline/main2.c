#include <stdio.h>
#include <stdlib.h>
#include "header2.h"

extern int timestwo(int input);
extern int plusfive(int input);

int main(void) {
  int start = 3;
  int intermediate = complicated1(start);
  printf("First result is %d\n", intermediate);
  intermediate = complicated2(start);
  printf("Second result is %d\n", intermediate);
  return 0;
}
