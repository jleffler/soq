#include <stdio.h>
#include <stdlib.h>
#include "header2.h"

int complicated1(int input) {
  int tmp = timestwo(input);
  return plusfive(tmp);
}
