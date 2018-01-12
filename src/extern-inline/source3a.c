#include <stdio.h>
#include <stdlib.h>
#include "header3.h"

int complicated1(int input) {
  int tmp = timestwo(input);
  return plusfive(tmp);
}
