#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

int complicated1(int input) {
  int tmp = timestwo(input);
  return plusfive(tmp);
}
