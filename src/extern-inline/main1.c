#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

int main(void) {
  int start = 3;
  int intermediate = complicated1(start);
  printf("First result is %d\n", intermediate);
  intermediate = complicated2(start);
  printf("Second result is %d\n", intermediate);
  return 0;
}
