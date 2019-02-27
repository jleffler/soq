#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

int complicated2(int input) {
  int tmp = plusfive(input);
  return timestwo(tmp);
}
