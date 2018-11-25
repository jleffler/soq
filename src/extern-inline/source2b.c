#include <stdio.h>
#include <stdlib.h>
#include "header2.h"

int complicated2(int input) {
  int tmp = plusfive(input);
  return timestwo(tmp);
}
